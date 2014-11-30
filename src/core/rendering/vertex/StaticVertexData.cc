#include "StaticVertexData.h"

#include "../buffers/IGpuBuffer.h"

namespace glove {

StaticVertexData::StaticVertexData(const VertexLayout& vertexLayout, const VertexBufferBindingMap& buffers,
                                   std::size_t numVertices)
    : bufferBindingMap(buffers), vertexLayout(vertexLayout), vertexCount(numVertices) {
}

const IGpuBufferPtr& StaticVertexData::GetGpuBuffer(std::size_t index) const {
    VertexBufferBindingMap::const_iterator it = bufferBindingMap.find(index);
    return it->second;
}

const std::size_t StaticVertexData::GetVertexCount() const {
    return vertexCount;
}

const VertexLayout& StaticVertexData::GetVertexLayout() const {
    return vertexLayout;
}

const std::size_t StaticVertexData::GetGpuBufferCount() const {
    return bufferBindingMap.size();
}

void StaticVertexData::BindAllBuffers() {
    for (const auto& bufferBinding : bufferBindingMap) {
        bufferBinding.second->Bind();
    }
}

} // namespace glove