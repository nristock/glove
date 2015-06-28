#pragma once

#include <glove/GloveApi.hpp>
#include <glove/rendering/RenderResourceFactory.hpp>


namespace glove {
namespace gl {
class GLOVE_API_EXPORT GLRenderResourceFactory : public RenderResourceFactory {
  public:
    virtual std::unique_ptr<VertexBinding> CreateVertexBinding(const std::unordered_map<uint8, VertexElement>& shaderAttributeBindings, const std::vector<VertexBufferHandle>& vertexStreams) const;
    virtual std::unique_ptr<VertexBuffer> CreateVertexBuffer() const;
    virtual std::unique_ptr<Texture2D> CreateTexture2D(uint32 width, uint32 height, glove::PixelFormat format) const;

    virtual std::unique_ptr<IndexBuffer> CreateIndexBuffer() const;

    virtual std::unique_ptr<VertexShader> CreateVertexShader(const char* source,
                                                             const ShaderParameterMap& shaderParameterMap) const;

    virtual std::unique_ptr<FragmentShader> CreateFragmentShader(const char* source) const;

    virtual std::unique_ptr<ShaderProgram> CreateShaderProgram(std::shared_ptr<VertexShader> vertexShader,
                                                               std::shared_ptr<FragmentShader> fragmentShader) const;
};

}
} /* namespace glove */