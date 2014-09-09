/*
 * VertexAttributeBuffer.h
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#ifndef VERTEXATTRIBUTEBUFFER_H_
#define VERTEXATTRIBUTEBUFFER_H_

#include "VertexLayoutAttribute.h"

#include <map>

#include "core/GloveFwd.h"
#include "GPUBuffer.h"
#include "core/GloveObject.h"
#include "shader/MappedVertexAttribute.h"

namespace glove {

class VertexAttributeBuffer: public GPUBuffer {
	GLOVE_MEM_ALLOC_FUNCS("VertexAttributeBuffer");
public:
	VertexAttributeBuffer(GLenum usage, GLintptr offset, GLsizei stride);
	virtual ~VertexAttributeBuffer();

	void DefineVertexAttribute(MappedVertexAttribute, GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset);

	const std::map<MappedVertexAttribute, VLDPtr>& getVertexLayout() const {
		return vertexLayout;
	}

	GLsizei getStride() const {
		return stride;
	}

private:
	GLintptr offset;
	GLsizei stride;

	std::map<MappedVertexAttribute, VLDPtr> vertexLayout;
};

} /* namespace glove */

#endif /* VERTEXATTRIBUTEBUFFER_H_ */
