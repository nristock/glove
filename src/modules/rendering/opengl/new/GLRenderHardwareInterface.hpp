#pragma once

#include <cstring>
#include <vector>

#include <glove/CommonTypes.hpp>
#include <glove/rendering/RenderHardwareInterface.hpp>
#include <glove/rendering/RenderTarget.hpp>
#include <glove/rendering/ApplicationViewport.hpp>

#include "../internal/OpenGLWrapper.hpp"
#include "GLState.hpp"
#include "GLTexture.hpp"
#include "GLShader.hpp"

namespace glove {
namespace gl {
class GLRenderHardwareInterface : public RenderHardwareInterface {
  public:
    virtual void SetViewport(int32 x, int32 y, int32 width, int32 height) override;
    virtual void SetScissorRect(int32 x, int32 y, int32 width, int32 height) override;

    virtual void SetRenderTargets(const std::vector<RenderTarget>& colorTargets,
                                  const RenderTarget& depthStencilTarget) override;
    virtual std::unique_ptr<RenderResourceFactory> CreateResourceFactory() const override;
    virtual void EnableVertexBinding(const std::shared_ptr<VertexBinding>& vertexBinding) override;
    virtual void EnableShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram) override;
    virtual void SetUniformParameter(const std::shared_ptr<UniformParameter::UniformIndex>& uniformParameter, const glm::mat4& value) override;
    virtual void DrawIndexedPrimitive(const std::shared_ptr<IndexBuffer>& indexBuffer, const uint32& firstIndex,
                                      const uint32& lastIndex) override;

    virtual void BindTexture2D(const std::shared_ptr<Texture2D>& texture, const uint32& slot);


    virtual void SetIntUniformParameter(const std::shared_ptr<UniformParameter::UniformIndex>& uniformParameter,
                                        const uint32& value);

    virtual void BeginFrame(const std::shared_ptr<ViewportClient>& viewportClient) override;
    virtual void EndFrame(const std::shared_ptr<ViewportClient>& viewportClient, const RenderTarget& presentSource) override;

    void BlitToDefaultFramebuffer(const RenderTarget& source, int width, int height);


    virtual void ClearFramebuffer(const bool& clearColor, const bool& clearDepth, const bool& clearStencil);

  protected:
    void SetColorTargets(const std::vector<RenderTarget>& colorTargets);
    void SetDepthStencilTarget(const RenderTarget& depthTarget);

  private:
    GLuint GetTextureResource(const Texture2D& texture) const {
        return dynamic_cast<const GLTexture2D&>(texture).GetResource();
    }

    void InitStandardFramebuffer();

    void UpdateViewportInContext();
    void UpdateScissorInContext();
    void UpdateFramebufferInContext();
    void UpdateRenderTargetsInContext();
    void UpdateDepthStencilTargetInContext();
    void UpdateVertexBindingInContext();
    void UpdateShaderProgramInContext();
    void UpdateTexturesInContext();
    void UpdateDepthTestInContext();
    void UpdateStencilTestInContext();

    void UpdateIndexBufferInContext(IndexBuffer* indexBuffer);

    GLuint standardFramebuffer;
    OpenGLContextState contextState;
    OpenGLContextState pendingState;
};
}
} // namespace glove
