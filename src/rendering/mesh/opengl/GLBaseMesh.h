#ifndef RENDERING_MESH_OPENGL_GLBASEMESH_H_
#define RENDERING_MESH_OPENGL_GLBASEMESH_H_

#include <gl/glew.h>

#include "memory/GloveMemory.h"

namespace glove {

class GLBaseMesh {
	GLOVE_MEM_ALLOC_FUNCS("GLBaseMesh")
public:
	virtual ~GLBaseMesh() {};

	const GLuint GetVertexArrayId() const { return vertexArrayId; }

protected:
	/** The Vertex Array Object ID */
	GLuint vertexArrayId;
};


} // namespace glove

#endif