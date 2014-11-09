#include "IndexData.h"

#include <core/GpuBufferManager.h>

namespace glove {

IndexData::IndexData(const GpuBufferManagerPtr& gpuBufferManager) :
	EnableProfilable() {
    indexBuffer = gpuBufferManager->CreateIndexBuffer();
}

IndexData::~IndexData() {

}

IGpuBufferPtr const IndexData::GetBuffer() const {
    return indexBuffer;
}

void IndexData::SetIndexCount(size_t count) {
    indexCount = count;
}

size_t const IndexData::GetIndexCount() const {
    return indexCount;
}
} // namespace glove