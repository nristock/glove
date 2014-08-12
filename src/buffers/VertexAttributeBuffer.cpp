/*
 * VertexAttributeBuffer.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#include <GL/glew.h>

#include "VertexAttributeBuffer.h"

namespace glove {
namespace gl {
namespace buffers {

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

void VertexAttributeBuffer::DefineVertexLayout(ushort attributeIdentifier,
		GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset) {
	vertexLayout[attributeIdentifier] = VLDPtr(new VertexLayoutDefinition(attributeIdentifier, size, type, normalized, relativeOffset));
}

} /* namespace buffers */
} /* namespace gl */
} /* namespace glove */


