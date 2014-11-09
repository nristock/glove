#include "VertexData.h"

#include <core/rendering/vertex/VertexLayout.h>

namespace glove {

VertexData::VertexData() :
    vertexLayout(),
	EnableProfilable() {

}

VertexData::~VertexData() {

}

const IGpuBufferPtr& VertexData::GetBuffer(unsigned short index) const {
    VertexBufferBindingMap::const_iterator it = bufferBindingMap.find(index);
    return it->second;
}

void VertexData::SetBufferBinding(unsigned short index, const IGpuBufferPtr& buffer) {
    bufferBindingMap[index] = buffer;
}

void VertexData::SetVertexCount(size_t vertexCount) {
    this->vertexCount = vertexCount;
}

size_t VertexData::GetVertexCount() const {
    return vertexCount;
}

VertexLayout* VertexData::GetVertexLayout() {
    return &vertexLayout;
}

VertexData::VertexBufferBindingMap const& VertexData::GetBindings() const {
    return bufferBindingMap;
}

size_t VertexData::GetBufferCount() const {
    return bufferBindingMap.size();
}
} // namespace glove