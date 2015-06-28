#include "GLRenderResourceFactory.hpp"
#include "GLVertexBinding.hpp"
#include "GLGpuBuffer.hpp"
#include "GLTexture.hpp"
#include "GLShader.hpp"

namespace BlueDwarf {
namespace gl {

std::unique_ptr<VertexBinding> GLRenderResourceFactory::CreateVertexBinding(const std::unordered_map<uint8, VertexElement>& shaderAttributeBindings, const std::vector<VertexBufferHandle>& vertexStreams) const {
    return std::make_unique<GLVertexBinding>(shaderAttributeBindings, vertexStreams);
}

std::unique_ptr<VertexBuffer> GLRenderResourceFactory::CreateVertexBuffer() const {
    return std::make_unique<GLVertexBuffer>();
}

std::unique_ptr<Texture2D> GLRenderResourceFactory::CreateTexture2D(uint32 width, uint32 height, PixelFormat format) const {
    return std::make_unique<GLTexture2D>(width, height, format);
}

std::unique_ptr<IndexBuffer> GLRenderResourceFactory::CreateIndexBuffer() const {
    return std::make_unique<GLIndexBuffer>();
}

std::unique_ptr<VertexShader> GLRenderResourceFactory::CreateVertexShader(const char* source,
                                                                          const ShaderParameterMap& shaderParameterMap) const {
    return std::make_unique<GLVertexShader>(source, shaderParameterMap);
}

std::unique_ptr<FragmentShader> GLRenderResourceFactory::CreateFragmentShader(const char* source) const {
    return std::make_unique<GLFragmentShader>(source);
}

std::unique_ptr<ShaderProgram> GLRenderResourceFactory::CreateShaderProgram(std::shared_ptr<VertexShader> vertexShader,
                                                                            std::shared_ptr<FragmentShader> fragmentShader) const {
    return std::make_unique<GLShaderProgram>(vertexShader, fragmentShader);
}
}
}