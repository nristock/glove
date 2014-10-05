#include <GL/glew.h>
#include <GL/gl.h>

#include "GLGpuBuffer.h"

namespace glove {
	
GLGpuBuffer::GLGpuBuffer(BufferUsage usage, GLenum target) : GPUBuffer(), target(target), usage(usage) {
	glGenBuffers(1, &bufferId);
}

GLGpuBuffer::~GLGpuBuffer() {
	glDeleteBuffers(1, &bufferId);
}

void GLGpuBuffer::Bind() {
	glBindBuffer(target, bufferId);
}

void GLGpuBuffer::Unbind() {
	glBindBuffer(target, 0);
}

void GLGpuBuffer::WriteData(size_t sizeInBytes, const void* data) {
	Bind();

	switch (usage) {
	case BU_STATIC:
		glBufferData(target, sizeInBytes, data, GL_STATIC_DRAW);
		break;
	}	
}

} // namespace glove