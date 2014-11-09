#include "IndexData.h"

#include "core/GloveCore.h"
#include "core/GpuBufferManager.h"

namespace glove {

IndexData::IndexData(const GpuBufferManagerPtr& gpuBufferManager) :
	EnableProfilable() {
    indexBuffer = gpuBufferManager->CreateIndexBuffer();
}

IndexData::~IndexData() {

}

} // namespace glove