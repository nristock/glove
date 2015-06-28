#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "glove/GloveApi.hpp"
#include "glove/rendering/VertexLayout.hpp"

namespace glove {
class VertexBinding;
class VertexBuffer;
using VertexBufferHandle = std::shared_ptr<VertexBuffer>;

class IndexBuffer;

class Texture2D;
struct RenderTarget;

class VertexShader;
class FragmentShader;
class ShaderProgram;

enum class PixelFormat;

/**
* The RenderResourceFactory provides methods to create hardware resources. Implementation details are up to the
* implementing renderer.
*/
class GLOVE_API_EXPORT RenderResourceFactory {
  public:
    virtual ~RenderResourceFactory() = default;

    virtual std::unique_ptr<VertexBinding>
    CreateVertexBinding(const std::unordered_map<uint8, VertexElement>& shaderAttributeBindings,
                        const std::vector<VertexBufferHandle>& vertexStreams) const = 0;
    virtual std::unique_ptr<VertexBuffer> CreateVertexBuffer() const = 0;
    virtual std::unique_ptr<IndexBuffer> CreateIndexBuffer() const = 0;
    virtual std::unique_ptr<Texture2D> CreateTexture2D(uint32 width, uint32 height,
                                                       glove::PixelFormat format) const = 0;

    virtual std::unique_ptr<VertexShader> CreateVertexShader(const char* source, const ShaderParameterMap& shaderParameterMap) const = 0;
    virtual std::unique_ptr<FragmentShader> CreateFragmentShader(const char* source) const = 0;
    virtual std::unique_ptr<ShaderProgram> CreateShaderProgram(std::shared_ptr<VertexShader> vertexShader, std::shared_ptr<FragmentShader> fragmentShader) const = 0;

  protected:
    RenderResourceFactory() = default;
};

} /* namespace glove */