/*
 * GPUBuffer.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#include <GL/glew.h>

#include "GPUBuffer.h"

namespace glove {
namespace gl {
namespace buffers {

GPUBuffer::GPUBuffer(GLenum target, GLenum usage) : target(target), usage(usage) {
	glGenBuffers(1, &bufferId);

}

GPUBuffer::~GPUBuffer() {
	glDeleteBuffers(1, &bufferId);
}

void GPUBuffer::Bind() {
	glBindBuffer(target, bufferId);
}

void GPUBuffer::Unbind() {
	glBindBuffer(target, 0);
}

void GPUBuffer::FillData(GLsizeiptr sizeInBytes, const GLvoid* data) {
	Bind();
	glBufferData(target, sizeInBytes, data, usage);
}

} /* namespace buffers */
} /* namespace gl */
} /* namespace glove */
