/*
 * VertexLayoutDefinition.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef VERTEXLAYOUTDEFINITION_H_
#define VERTEXLAYOUTDEFINITION_H_

#include <GL/gl.h>
#include <memory>

namespace glove {
namespace gl {
namespace buffers {

class VertexLayoutDefinition {
public:
	VertexLayoutDefinition(ushort attributeIdentifier, GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset);
	virtual ~VertexLayoutDefinition();

	ushort getAttributeIdentifier() const {
		return attributeIdentifier;
	}

	void setAttributeIdentifier(ushort attributeIdentifier) {
		this->attributeIdentifier = attributeIdentifier;
	}

	GLboolean getNormalized() const {
		return normalized;
	}

	void setNormalized(GLboolean normalized) {
		this->normalized = normalized;
	}

	GLuint getRelativeOffset() const {
		return relativeOffset;
	}

	void setRelativeOffset(GLuint relativeOffset) {
		this->relativeOffset = relativeOffset;
	}

	GLint getSize() const {
		return size;
	}

	void setSize(GLint size) {
		this->size = size;
	}

	GLenum getType() const {
		return type;
	}

	void setType(GLenum type) {
		this->type = type;
	}

private:
	ushort attributeIdentifier;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLuint relativeOffset;
};

typedef std::shared_ptr<VertexLayoutDefinition> VertexLayoutDefinitionPtr;
typedef VertexLayoutDefinitionPtr VLDPtr;

} /* namespace buffers */
} /* namespace gl */
} /* namespace glove */

#endif /* VERTEXLAYOUTDEFINITION_H_ */
