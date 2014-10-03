#include "ManagedIndexData.h"

#include "buffers/GPUBuffer.h"

namespace glove {
	
ManagedIndexData::ManagedIndexData() : IndexData() {

}

ManagedIndexData::~ManagedIndexData() {
	
}

void ManagedIndexData::FlushBuffer() const {
	indexBuffer->WriteData(GetIndexCount() * sizeof(unsigned int), &indices[0]);
}

} // namespace glove