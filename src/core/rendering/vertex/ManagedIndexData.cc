#include "ManagedIndexData.h"

#include <core/rendering/buffers/IGpuBuffer.h>

namespace glove {

ManagedIndexData::ManagedIndexData(const GpuBufferManagerPtr& gpuBufferManager) : IndexData(gpuBufferManager), EnableProfilable() {
}

ManagedIndexData::~ManagedIndexData() {

}

void ManagedIndexData::FlushBuffer() const {
    indexBuffer->WriteData(GetIndexCount() * sizeof(unsigned int), &indices[0]);
}

} // namespace glove