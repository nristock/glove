/*
 * VertexLayoutDefinition.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef VERTEXLAYOUTDEFINITION_H_
#define VERTEXLAYOUTDEFINITION_H_

#include <GL/glew.h>
#include <GL/gl.h>

namespace glove {

struct VertexLayoutDefinition {
public:
	VertexLayoutDefinition(unsigned short attributeIdentifier, GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset);
	virtual ~VertexLayoutDefinition();

	unsigned short attributeIdentifier;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLuint relativeOffset;
};

} /* namespace glove */

#endif /* VERTEXLAYOUTDEFINITION_H_ */
