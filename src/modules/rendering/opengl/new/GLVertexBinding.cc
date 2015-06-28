#include <glove/rendering/RenderCommandList.hpp>
#include "GLGpuBuffer.hpp"
#include "GLVertexBinding.hpp"
#include "VertexElementUtils.hpp"

namespace glove {
namespace gl {
GLVertexBinding::GLVertexBinding(const std::unordered_map<uint8, VertexElement>& shaderAttributeBindings,
                                 const std::vector<VertexBufferHandle>& vertexStreams) : VertexBinding(shaderAttributeBindings, vertexStreams) {
    GL::GenVertexArrays(1, &vaoId);
    InitVao();
}

GLVertexBinding::~GLVertexBinding() {
    GL::DeleteVertexArrays(1, &vaoId);
}

void GLVertexBinding::InitVao() {
    GL::BindVertexArray(vaoId);

    for (uint8 i = 0; i < vertexStreams.size(); ++i) {
        dynamic_cast<GLGpuBufferBase*>(vertexStreams[i].get())->GLBind();

        for (auto& mapEntry : shaderAttributeBindings) {
            const VertexElement& vertexElement = mapEntry.second;
            if (mapEntry.second.streamIndex == i) {
                GL::VertexAttribPointer(mapEntry.first, VertexElementTypeToElementCount(vertexElement.type), VertexElementTypeToGlType(vertexElement.type), GL_FALSE,
                                        vertexElement.stride, (char*)nullptr + vertexElement.offset);
                GL::EnableVertexAttribArray(mapEntry.first);
            }
        }
    }
}

}
} /* namespace glove */