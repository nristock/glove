#ifndef BUFFERS_VERTEXLAYOUTATTRIBUTE_H_
#define BUFFERS_VERTEXLAYOUTATTRIBUTE_H_

#include <GL/glew.h>
#include <GL/gl.h>

#include "core/GloveObject.h"
#include "shader/MappedVertexAttribute.h"

namespace glove {

/*
 * Represents a single vertex layout attribute.
 */
struct VertexLayoutAttribute : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("VertexLayoutAttribute");
public:
	VertexLayoutAttribute(MappedVertexAttribute attributeIdentifier, GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset);
	virtual ~VertexLayoutAttribute();

	MappedVertexAttribute attributeIdentifier;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLuint relativeOffset;
};

} /* namespace glove */

#endif 
