#include "GpuBufferManager.h"

#include "buffers/opengl/GLGpuBuffer.h"

namespace glove {
	
GpuBufferManager::GpuBufferManager() {

}

GpuBufferManager::~GpuBufferManager() {
	
}

GPUBufferPtr GpuBufferManager::CreateVertexBuffer(BufferUsage bufferUsage) {
	GLGpuBuffer* gpuBuffer = new GLGpuBuffer(bufferUsage, GL_ARRAY_BUFFER);
	return GPUBufferPtr(gpuBuffer);
}

GPUBufferPtr GpuBufferManager::CreateIndexBuffer() {
	GLGpuBuffer* gpuBuffer = new GLGpuBuffer(BU_STATIC, GL_ELEMENT_ARRAY_BUFFER);
	return GPUBufferPtr(gpuBuffer);
}

} // namespace glove