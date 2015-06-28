#include "glove/rendering/RenderCommandList.hpp"
#include "glove/rendering/RenderTarget.hpp"

namespace BlueDwarf {

void RenderCommandList::SetRenderTargets(const std::vector<RenderTarget>& colorTargets,
                                         const RenderTarget& depthStencilTarget) {
    for (const auto& renderTarget : colorTargets) {
        if (renderTarget.HasTexture()) {
            DebugAssert(IsColorFormat(renderTarget.GetTexture()->GetPixelFormat()));
        }
    }

    if (depthStencilTarget.HasTexture()) {
        DebugAssert(IsDepthStencilFormat(depthStencilTarget.GetTexture()->GetPixelFormat()));
    }

    commands.push_back(std::make_unique<SetRenderTargetsCommand>(colorTargets, depthStencilTarget));
}

void RenderCommandList::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) {
    commands.push_back(std::make_unique<SetViewportCommand>(x, y, width, height));
}

void RenderCommandList::SetScissorRect(uint32 x, uint32 y, uint32 width, uint32 height) {
    commands.push_back(std::make_unique<SetScissorRectCommand>(x, y, width, height));
}

void RenderCommandList::BindTexture2D(Texture2DHandle texture, uint32 slot) {
    commands.push_back(std::make_unique<BindTexture2DCommand>(texture, slot));
}

void RenderCommandList::SetIntUniform(UniformParameter::UniformIndex::Handle uniformParameterIndex, uint32 value) {
    commands.push_back(std::make_unique<SetIntUniformParameterCommand>(uniformParameterIndex, value));
}

void RenderCommandList::EnableVertexBinding(VertexBindingHandle vertexBinding) {
    commands.push_back(std::make_unique<EnableVertexBindingCommand>(vertexBinding));
}

void RenderCommandList::DrawIndexed(IndexBufferHandle indexBuffer, uint32 firstIndex, uint32 lastIndex) {
    commands.push_back(std::make_unique<DrawIndexedPrimitiveCommand>(indexBuffer, firstIndex, lastIndex));
}

void RenderCommandList::SetUniform(UniformParameter::UniformIndex::Handle uniformParameterIndex, glm::mat4 value) {
    commands.push_back(std::make_unique<SetUniformParameterCommand>(uniformParameterIndex, std::move(value)));
}

void RenderCommandList::EnableShaderProgram(ShaderProgramHandle shaderProgram) {
    commands.push_back(std::make_unique<EnableShaderProgramCommand>(std::move(shaderProgram)));
}

void RenderCommandList::ClearFramebuffer(bool clearColor, bool clearDepth, bool clearStencil) {
    commands.push_back(std::make_unique<ClearFramebufferCommand>(clearColor, clearDepth, clearStencil));
}

void RenderCommandList::BeginFrame(ViewportClientHandle viewportClient) {
    commands.push_back(std::make_unique<BeginFrameCommand>(viewportClient));
}

void RenderCommandList::EndFrame(ViewportClientHandle viewportClient, const RenderTarget& presentSource) {
    commands.push_back(std::make_unique<EndFrameCommand>(viewportClient, presentSource));
}

void RenderCommandList::Execute(RenderHardwareInterface& rhi) {
    for (auto& command : commands) {
        command->Execute(rhi);
    }
}

void RenderCommandList::Visualize(std::ostream& ostream) {
    for(auto& command : commands) {
        command->Visualize(ostream);
        ostream << "\n";
    }
}
}