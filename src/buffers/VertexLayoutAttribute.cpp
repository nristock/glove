#include "VertexLayoutAttribute.h"

namespace glove {

VertexLayoutAttribute::VertexLayoutAttribute(MappedVertexAttribute attributeIdentifier,
		GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset)
		: attributeIdentifier(attributeIdentifier), size(size), type(type), normalized(normalized), relativeOffset(relativeOffset) {
}

VertexLayoutAttribute::~VertexLayoutAttribute() {
	// TODO Auto-generated destructor stub
}

} /* namespace glove */
