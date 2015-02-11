#include "glove/rendering/vertex/StaticIndexData.hpp"
#include "glove/rendering/buffers/IGpuBuffer.hpp"

namespace glove {

StaticIndexData::StaticIndexData(const IGpuBufferPtr& indexBuffer, std::size_t numIndices)
    : indexBuffer(indexBuffer), indexCount(numIndices) {
}

const IGpuBufferPtr& StaticIndexData::GetGpuBuffer() const {
    return indexBuffer;
}

size_t const StaticIndexData::GetIndexCount() const {
    return indexCount;
}

void StaticIndexData::BindBuffer() {
    GetGpuBuffer()->Bind();
}

} // namespace glove