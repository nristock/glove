/*
 * VertexAttributeBuffer.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#include "VertexAttributeBuffer.h"

#include "VertexLayoutDefinition.h"

namespace glove {

VertexAttributeBuffer::VertexAttributeBuffer(
		GLenum usage,
		GLintptr offset,
		GLsizei stride) :
				GPUBuffer(GL_ARRAY_BUFFER, usage),
				offset(offset),
				stride(stride)
{
}

VertexAttributeBuffer::~VertexAttributeBuffer() {

}

void VertexAttributeBuffer::DefineVertexLayout(unsigned short attributeIdentifier,
		GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset) {
	vertexLayout[attributeIdentifier] = VLDPtr(new VertexLayoutDefinition(attributeIdentifier, size, type, normalized, relativeOffset));
}

} /* namespace glove */


