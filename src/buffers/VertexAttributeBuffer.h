/*
 * VertexAttributeBuffer.h
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#ifndef VERTEXATTRIBUTEBUFFER_H_
#define VERTEXATTRIBUTEBUFFER_H_

#include <map>
#include "VertexLayoutDefinition.h"
#include "GPUBuffer.h"


namespace glove {
namespace gl {
namespace buffers {

class VertexAttributeBuffer: public GPUBuffer {
public:
	VertexAttributeBuffer(GLenum usage, GLintptr offset, GLsizei stride);
	virtual ~VertexAttributeBuffer();

	void DefineVertexLayout(ushort attributeIdentifier, GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset);

	const std::map<ushort, VLDPtr>& getVertexLayout() const {
		return vertexLayout;
	}

	GLsizei getStride() const {
		return stride;
	}

private:
	GLintptr offset;
	GLsizei stride;

	std::map<ushort, VLDPtr> vertexLayout;
};

typedef std::shared_ptr<VertexAttributeBuffer> VABPtr;

} /* namespace buffers */
} /* namespace gl */
} /* namespace glove */

#endif /* VERTEXATTRIBUTEBUFFER_H_ */
