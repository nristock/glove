#include "VertexData.h"

#include "rendering/vertex/VertexLayout.h"

namespace glove {
	
VertexData::VertexData() {
}

VertexData::~VertexData() {
	
}

const GPUBufferPtr& VertexData::GetBuffer(unsigned short index) const {
	VertexBufferBindingMap::const_iterator it = bufferBindingMap.find(index);
	return it->second;
}

void VertexData::SetBufferBinding(unsigned short index, const GPUBufferPtr& buffer) {
	bufferBindingMap[index] = buffer;
}

} // namespace glove