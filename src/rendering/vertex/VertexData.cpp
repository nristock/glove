#include "VertexData.h"

#include "rendering/vertex/VertexLayout.h"

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

} // namespace glove