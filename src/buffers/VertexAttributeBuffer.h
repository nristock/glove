/*
 * VertexAttributeBuffer.h
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#ifndef VERTEXATTRIBUTEBUFFER_H_
#define VERTEXATTRIBUTEBUFFER_H_

#include "VertexLayoutDefinition.h"

#include <map>

#include "core/GloveFwd.h"
#include "GPUBuffer.h"

namespace glove {

class VertexAttributeBuffer: public GPUBuffer {
public:
	VertexAttributeBuffer(GLenum usage, GLintptr offset, GLsizei stride);
	virtual ~VertexAttributeBuffer();

	void DefineVertexLayout(unsigned short attributeIdentifier, GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset);

	const std::map<unsigned short, VLDPtr>& getVertexLayout() const {
		return vertexLayout;
	}

	GLsizei getStride() const {
		return stride;
	}

private:
	GLintptr offset;
	GLsizei stride;

	std::map<unsigned short, VLDPtr> vertexLayout;
};

} /* namespace glove */

#endif /* VERTEXATTRIBUTEBUFFER_H_ */
