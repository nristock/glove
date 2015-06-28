#include "GLRenderHardwareInterface.hpp"
#include "GLWindow.hpp"
#include "GLRenderResourceFactory.hpp"
#include "GLVertexBinding.hpp"
#include "GLGpuBuffer.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <glove/log/Log.hpp>

namespace {
using BlueDwarf::gl::GL;

struct GLErrorScope {
  public:
    GLErrorScope(const char* function, const char* file, int line) : function(function), file(file), line(line) {
        GLenum scopeEnterError = GL::GetError();

        if (IsErrorCode(scopeEnterError)) {
            LogError(scopeEnterError, true);
        }
    }

    ~GLErrorScope() {
        GLenum scopeExitError = GL::GetError();

        if (IsErrorCode(scopeExitError)) {
            LogError(scopeExitError, false);
        }
    }

  private:
    bool IsErrorCode(GLenum code) { return code != GL_NO_ERROR; }

    void LogError(GLenum errorCode, bool before) {
        static const std::array<const char*, 8> errorStrings = {"GL_INVALID_ENUM",
                                                                "GL_INVALID_VALUE",
                                                                "GL_INVALID_OPERATION",
                                                                "GL_STACK_OVERFLOW",
                                                                "GL_STACK_UNDERFLOW",
                                                                "GL_OUT_OF_MEMORY",
                                                                "GL_INVALID_FRAMEBUFFER_OPERATION",
                                                                "GL_CONTEXT_LOST"};

        L_ERROR(fmt::format("OpenGL Error {0}: {1} in {2} ({3}:{4})", before ? "before" : "after",
                            errorStrings[errorCode - GL_INVALID_ENUM], function, file, line));
    }

    const std::string function;
    const std::string file;
    const int line;
};
}

#define VERIFY_GL() GLErrorScope glErrorScope(__FUNCTION__, __FILE__, __LINE__)

namespace BlueDwarf {
namespace gl {
void GLRenderHardwareInterface::SetViewport(int32 x, int32 y, int32 width, int32 height) {
    pendingState.viewport.min.x = x;
    pendingState.viewport.min.y = y;
    pendingState.viewport.max.x = x + width;
    pendingState.viewport.max.y = y + height;

    Check(pendingState.viewport.min.x < pendingState.viewport.max.x);
    Check(pendingState.viewport.min.y < pendingState.viewport.max.y);
}

void GLRenderHardwareInterface::InitStandardFramebuffer() {
    if (standardFramebuffer != 0) {
        pendingState.framebuffer = standardFramebuffer;
        return;
    }

    VERIFY_GL();
    GL::GenFramebuffers(1, &standardFramebuffer);

    pendingState.framebuffer = standardFramebuffer;
}

void GLRenderHardwareInterface::UpdateViewportInContext() {
    if (contextState.viewport == pendingState.viewport) {
        return;
    }

    VERIFY_GL();
    GL::Viewport(pendingState.viewport.min.x, pendingState.viewport.min.y,
                 pendingState.viewport.max.x - pendingState.viewport.min.x,
                 pendingState.viewport.max.y - pendingState.viewport.min.y);

    contextState.viewport = pendingState.viewport;
}

void GLRenderHardwareInterface::SetScissorRect(int32 x, int32 y, int32 width, int32 height) {
    pendingState.enableScissor = true;
    pendingState.scissor.min.x = x;
    pendingState.scissor.min.y = y;
    pendingState.scissor.max.x = x + width;
    pendingState.scissor.max.y = y + height;

    Check(pendingState.scissor.min.x < pendingState.scissor.max.x);
    Check(pendingState.scissor.min.y < pendingState.scissor.max.y);
}

void GLRenderHardwareInterface::UpdateScissorInContext() {
    if (pendingState.enableScissor == contextState.enableScissor && pendingState.scissor == contextState.scissor) {
        return;
    }

    if (pendingState.enableScissor != contextState.enableScissor) {
        contextState.enableScissor = pendingState.enableScissor;

        if (pendingState.enableScissor) {
            VERIFY_GL();
            GL::Enable(GL_SCISSOR_TEST);
        } else {
            VERIFY_GL();
            GL::Disable(GL_SCISSOR_TEST);
            return;
        }
    }

    if (pendingState.scissor != contextState.scissor) {
        VERIFY_GL();
        GL::Scissor(pendingState.scissor.min.x, pendingState.scissor.min.y,
                    pendingState.scissor.max.x - pendingState.scissor.min.x,
                    pendingState.scissor.max.y - pendingState.scissor.min.y);

        contextState.viewport = pendingState.viewport;
    }
}

void GLRenderHardwareInterface::SetDepthStencilTarget(const RenderTarget& depthTarget) {
    if (depthTarget.HasTexture()) {
        pendingState.enableDepthTest = true;
        pendingState.enableStencilTest = true;
        pendingState.depthStencilTarget = GetTextureResource(*depthTarget.GetTexture());
    } else {
        pendingState.enableDepthTest = false;
        pendingState.enableStencilTest = false;
        pendingState.depthStencilTarget = 0;
    }
}

void GLRenderHardwareInterface::SetColorTargets(const std::vector<RenderTarget>& colorTargets) {
    pendingState.renderTargets.fill(0);
    for (uint32 i = 0; i < colorTargets.size(); ++i) {
        pendingState.renderTargets[i] = GetTextureResource(*colorTargets[i].GetTexture());
    }
}

void GLRenderHardwareInterface::SetRenderTargets(const std::vector<RenderTarget>& colorTargets,
                                                 const RenderTarget& depthStencilTarget) {
    SetColorTargets(colorTargets);
    SetDepthStencilTarget(depthStencilTarget);
}

void GLRenderHardwareInterface::UpdateRenderTargetsInContext() {
    if (pendingState.renderTargets == contextState.renderTargets) {
        return;
    }

    InitStandardFramebuffer();
    UpdateFramebufferInContext();

    for (uint32 i = 0; i < pendingState.renderTargets.size(); ++i) {
        VERIFY_GL();
        GL::FramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, pendingState.renderTargets[i], 0);
    }

    contextState.renderTargets = pendingState.renderTargets;
}

void GLRenderHardwareInterface::UpdateDepthStencilTargetInContext() {
    if (pendingState.depthStencilTarget == contextState.depthStencilTarget) {
        return;
    }

    InitStandardFramebuffer();
    UpdateFramebufferInContext();

    VERIFY_GL();
    GL::FramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, pendingState.depthStencilTarget, 0);

    contextState.depthStencilTarget = pendingState.depthStencilTarget;
}

void GLRenderHardwareInterface::UpdateFramebufferInContext() {
    if (pendingState.framebuffer == contextState.framebuffer) {
        return;
    }

    VERIFY_GL();
    GL::BindFramebuffer(GL_FRAMEBUFFER, pendingState.framebuffer);

    contextState.framebuffer = pendingState.framebuffer;
}

std::unique_ptr<RenderResourceFactory> GLRenderHardwareInterface::CreateResourceFactory() const {
    return std::make_unique<GLRenderResourceFactory>();
}

void GLRenderHardwareInterface::EnableVertexBinding(const std::shared_ptr<VertexBinding>& vertexBinding) {
    pendingState.vao = dynamic_cast<GLVertexBinding*>(vertexBinding.get())->GetVaoId();
}

void GLRenderHardwareInterface::EnableShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram) {
    pendingState.shaderProgram = dynamic_cast<GLShaderProgram*>(shaderProgram.get())->GetProgramId();
}

void GLRenderHardwareInterface::SetUniformParameter(
    const std::shared_ptr<UniformParameter::UniformIndex>& uniformParameter, const glm::mat4& value) {
    UpdateShaderProgramInContext();

    auto glUniformIndex = dynamic_cast<GLUniformIndex*>(uniformParameter.get());
    GL::UniformMatrix4fv(glUniformIndex->GetUniformIndex(), 1, GL_FALSE, glm::value_ptr(value));
}

void GLRenderHardwareInterface::DrawIndexedPrimitive(const std::shared_ptr<IndexBuffer>& indexBuffer,
                                                     const uint32& firstIndex, const uint32& lastIndex) {
    UpdateFramebufferInContext();
    UpdateDepthStencilTargetInContext();
    UpdateRenderTargetsInContext();
    UpdateViewportInContext();
    UpdateScissorInContext();
    UpdateShaderProgramInContext();
    UpdateVertexBindingInContext();
    UpdateTexturesInContext();
    UpdateDepthTestInContext();
    UpdateStencilTestInContext();

    UpdateIndexBufferInContext(indexBuffer.get());

    VERIFY_GL();
    GL::DrawElements(GL_TRIANGLES,               // mode
                     lastIndex - firstIndex + 1, // count
                     GL_UNSIGNED_SHORT,          // type
                     (void*)0);
}

void GLRenderHardwareInterface::BeginFrame(const std::shared_ptr<ViewportClient>& viewportClient) {
    VERIFY_GL();

    auto glWindow = dynamic_cast<GLWindow*>(viewportClient.get());
    glWindow->MakeCurrent();
}

void GLRenderHardwareInterface::EndFrame(const std::shared_ptr<ViewportClient>& viewportClient, const RenderTarget& presentSource) {
    VERIFY_GL();
    auto glWindow = dynamic_cast<GLWindow*>(viewportClient.get());
    glWindow->GLFlush(presentSource, *this);
}

void GLRenderHardwareInterface::UpdateVertexBindingInContext() {
    if (pendingState.vao == contextState.vao) {
        return;
    }

    VERIFY_GL();
    GL::BindVertexArray(pendingState.vao);

    contextState.vao = pendingState.vao;
}

void GLRenderHardwareInterface::UpdateShaderProgramInContext() {
    if (pendingState.shaderProgram == contextState.shaderProgram) {
        return;
    }

    VERIFY_GL();
    GL::UseProgram(pendingState.shaderProgram);

    contextState.shaderProgram = pendingState.shaderProgram;
}

void GLRenderHardwareInterface::UpdateIndexBufferInContext(IndexBuffer* indexBuffer) {
    VERIFY_GL();

    auto glIndexBuffer = dynamic_cast<GLIndexBuffer*>(indexBuffer);
    glIndexBuffer->GLBind();
}

void GLRenderHardwareInterface::BindTexture2D(const std::shared_ptr<Texture2D>& texture, const uint32& slot) {
    DebugAssert(slot < pendingState.textures.max_size());
    pendingState.textures[slot] = GetTextureResource(*texture);
}

void GLRenderHardwareInterface::UpdateTexturesInContext() {
    if (pendingState.textures == contextState.textures) {
        return;
    }

    for (uint32 i = 0; i < pendingState.textures.size(); ++i) {
        {
            VERIFY_GL();
            GL::ActiveTexture(GL_TEXTURE0 + i);
        }

        {
            VERIFY_GL();
            GL::BindTexture(GL_TEXTURE_2D, pendingState.textures[i]);
        }
    }

    contextState.textures = pendingState.textures;
}

void GLRenderHardwareInterface::SetIntUniformParameter(
    const std::shared_ptr<UniformParameter::UniformIndex>& uniformParameter, const uint32& value) {
    UpdateShaderProgramInContext();

    VERIFY_GL();
    auto glUniformIndex = dynamic_cast<GLUniformIndex*>(uniformParameter.get());
    GL::Uniform1i(glUniformIndex->GetUniformIndex(), value);
}

void GLRenderHardwareInterface::ClearFramebuffer(const bool& clearColor, const bool& clearDepth,
                                                 const bool& clearStencil) {
    UpdateFramebufferInContext();
    UpdateRenderTargetsInContext();
    UpdateDepthStencilTargetInContext();

    VERIFY_GL();
    GL::Clear((GLbitfield)((clearColor ? GL_COLOR_BUFFER_BIT : 0) | (clearDepth ? GL_DEPTH_BUFFER_BIT : 0) |
                           (clearStencil ? GL_STENCIL_BUFFER_BIT : 0)));
}

void GLRenderHardwareInterface::UpdateDepthTestInContext() {
    if (pendingState.enableDepthTest == contextState.enableDepthTest) {
        return;
    }

    if (pendingState.enableDepthTest) {
        VERIFY_GL();
        GL::Enable(GL_DEPTH_TEST);
    } else {
        VERIFY_GL();
        GL::Disable(GL_DEPTH_TEST);
    }

    contextState.enableDepthTest = pendingState.enableDepthTest;
}

void GLRenderHardwareInterface::UpdateStencilTestInContext() {
    if (pendingState.enableStencilTest == contextState.enableStencilTest) {
        return;
    }

    if (pendingState.enableStencilTest) {
        VERIFY_GL();
        GL::Enable(GL_STENCIL_TEST);
    } else {
        VERIFY_GL();
        GL::Disable(GL_STENCIL_TEST);
    }

    contextState.enableStencilTest = pendingState.enableStencilTest;
}

void GLRenderHardwareInterface::BlitToDefaultFramebuffer(const RenderTarget& source, int width, int height) {
    pendingState.renderTargets.fill(0);
    pendingState.renderTargets[0] = GetTextureResource(*source.GetTexture());

    UpdateRenderTargetsInContext();

    VERIFY_GL();
    glBindFramebuffer(GL_READ_FRAMEBUFFER, contextState.framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebuffer(GL_FRAMEBUFFER, contextState.framebuffer);
}
}
}
