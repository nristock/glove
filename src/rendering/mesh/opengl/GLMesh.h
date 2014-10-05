#ifndef RENDERING_MESH_OPENGL_GLMESH_H_
#define RENDERING_MESH_OPENGL_GLMESH_H_

#include "rendering/mesh/Mesh.h"
#include "rendering/mesh/opengl/GLBaseMesh.h"

namespace glove {

/** OpenGL Mesh implementation; basically wraps VAO related calls. */
class GLMesh : public GLBaseMesh, public Mesh {
	GLOVE_MEM_ALLOC_FUNCS("GLMesh")
public:
	GLMesh(MaterialPtr material);
	virtual ~GLMesh();
	
	virtual void SetupRender(RenderOperation& renderOp, const FrameData& frameData);
	virtual void PostRender(RenderOperation& renderOp, const FrameData& frameData);
};


} // namespace glove

#endif