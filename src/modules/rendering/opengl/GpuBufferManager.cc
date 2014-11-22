#include "GpuBufferManager.h"

#include <core/opengl/GLGpuBuffer.h>

namespace glove {

	GpuBufferManager::GpuBufferManager() :
		EnableProfilable() {

}

GpuBufferManager::~GpuBufferManager() {

}

IGpuBufferPtr GpuBufferManager::CreateVertexBuffer(BufferUsage bufferUsage) {
	GLGpuBuffer* gpuBuffer = new GLGpuBuffer(bufferUsage, GL_ARRAY_BUFFER);
	return IGpuBufferPtr(gpuBuffer);
}

IGpuBufferPtr GpuBufferManager::CreateIndexBuffer() {
	GLGpuBuffer* gpuBuffer = new GLGpuBuffer(BU_STATIC, GL_ELEMENT_ARRAY_BUFFER);
	return IGpuBufferPtr(gpuBuffer);
}

} // namespace glove