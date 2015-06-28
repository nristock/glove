#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "glove/GloveApi.hpp"
#include "glove/rendering/MaterialProxy.hpp"

namespace glove {
class RenderResourceFactory;
struct RenderTarget;
class VertexBinding;
class ShaderProgram;
class IndexBuffer;
class ViewportClient;
class Texture2D;

/**
* The render hardware interface provides methods which allow to interact with the rendering hardware (API) in an
* abstract way.
*/
class GLOVE_API_EXPORT RenderHardwareInterface {
  public:
    virtual ~RenderHardwareInterface() = default;

    virtual std::unique_ptr<RenderResourceFactory> CreateResourceFactory() const = 0;

    // Begin of generated section, do not modify manually
    // [GENERATE:COMMAND_METHODS]
    virtual void SetViewport(int32 x, int32 y, int32 width, int32 height) = 0;
    virtual void SetScissorRect(int32 x, int32 y, int32 width, int32 height) = 0;
    virtual void SetRenderTargets(const std::vector<RenderTarget>& colorTargets,
                                  const RenderTarget& depthStencilTarget) = 0;
    virtual void EnableVertexBinding(const std::shared_ptr<VertexBinding>& vertexBinding) = 0;
    virtual void EnableShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram) = 0;
    virtual void BindTexture2D(const std::shared_ptr<Texture2D>& texture, const uint32& textureSlot) = 0;
    virtual void SetUniformParameter(const std::shared_ptr<UniformParameter::UniformIndex>& uniformParameter,
                                     const glm::mat4& value) = 0;
    virtual void SetIntUniformParameter(const std::shared_ptr<UniformParameter::UniformIndex>& uniformParameter,
                                        const uint32& value) = 0;
    virtual void DrawIndexedPrimitive(const std::shared_ptr<IndexBuffer>& indexBuffer, const uint32& firstIndex,
                                      const uint32& lastIndex) = 0;
    virtual void ClearFramebuffer(const bool& clearColor, const bool& clearDepth, const bool& clearStencil) = 0;
    virtual void BeginFrame(const std::shared_ptr<ViewportClient>& viewportClient) = 0;
    virtual void EndFrame(const std::shared_ptr<ViewportClient>& viewportClient, const RenderTarget& presentSource) = 0;
    // [\GENERATE:COMMAND_METHODS]
};

} /* namespace glove */