/*
 * VertexLayoutDefinition.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "VertexLayoutDefinition.h"

namespace glove {

VertexLayoutDefinition::VertexLayoutDefinition(unsigned short attributeIdentifier,
		GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset)
		: attributeIdentifier(attributeIdentifier), size(size), type(type), normalized(normalized), relativeOffset(relativeOffset) {
}

VertexLayoutDefinition::~VertexLayoutDefinition() {
	// TODO Auto-generated destructor stub
}

} /* namespace glove */
