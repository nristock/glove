#pragma once

#include <list>
#include <memory>

#include <glm/glm.hpp>

#include "glove/GloveApi.hpp"
#include "glove/rendering/RenderHardwareCommands.hpp"
#include "glove/rendering/Texture.hpp"
#include "glove/rendering/MaterialProxy.hpp"
#include "Material.hpp"

using namespace BlueDwarf;

namespace glove {
struct RenderTarget;

class VertexBinding;
using VertexBindingHandle = std::shared_ptr<VertexBinding>;

class IndexBuffer;
using IndexBufferHandle = std::shared_ptr<IndexBuffer>;

class ViewportClient;
using ViewportClientHandle = std::shared_ptr<ViewportClient>;

class GLOVE_API_EXPORT RenderCommandList {
  public:
    void SetRenderTargets(const std::vector<RenderTarget>& colorTargets, const RenderTarget& depthStencilTarget);
    void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height);
    void SetScissorRect(uint32 x, uint32 y, uint32 width, uint32 height);
    void BindTexture2D(Texture2DHandle texture, uint32 slot);
    void SetIntUniform(UniformParameter::UniformIndex::Handle uniformParameterIndex, uint32 value);
    void EnableVertexBinding(VertexBindingHandle vertexBinding);
    void DrawIndexed(IndexBufferHandle indexBuffer, uint32 firstIndex, uint32 lastIndex);
    void SetUniform(UniformParameter::UniformIndex::Handle uniformParameterIndex, glm::mat4 value);
    void EnableShaderProgram(ShaderProgramHandle shaderProgram);
    void ClearFramebuffer(bool clearColor, bool clearDepth, bool clearStencil);
    void BeginFrame(ViewportClientHandle viewportClient);
    void EndFrame(ViewportClientHandle viewportClient, const RenderTarget& presentSource);
    void Execute(RenderHardwareInterface& rhi);
    void Visualize(std::ostream& ostream);

  private:
    bool IsDepthStencilFormat(PixelFormat pixelFormat) {
        return pixelFormat == PixelFormat::Depth24Stencil8 || pixelFormat == PixelFormat::Depth32FStencil8;
    }
    bool IsColorFormat(PixelFormat pixelFormat) {
        return !IsDepthStencilFormat(pixelFormat) && pixelFormat != PixelFormat::Unknown;
    }

    std::list<std::unique_ptr<RenderHardwareCommand>> commands;
};
}
