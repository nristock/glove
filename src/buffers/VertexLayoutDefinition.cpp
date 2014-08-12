/*
 * VertexLayoutDefinition.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "VertexLayoutDefinition.h"

namespace glove {
namespace gl {
namespace buffers {

VertexLayoutDefinition::VertexLayoutDefinition(ushort attributeIdentifier,
		GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset)
		: attributeIdentifier(attributeIdentifier), size(size), type(type), normalized(normalized), relativeOffset(relativeOffset) {
}

VertexLayoutDefinition::~VertexLayoutDefinition() {
	// TODO Auto-generated destructor stub
}

} /* namespace buffers */
} /* namespace gl */
} /* namespace glove */
