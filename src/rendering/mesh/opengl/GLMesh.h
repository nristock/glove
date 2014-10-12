#pragma once

#include "rendering/mesh/Mesh.h"
#include "rendering/mesh/opengl/GLBaseMesh.h"
#include "rendering/opengl/GLRenderer.h"

namespace glove {

/** OpenGL Mesh implementation; basically wraps VAO related calls. */
class GLMesh : public GLBaseMesh, public Mesh {
	GLOVE_MEM_ALLOC_FUNCS("GLMesh")
public:
	GLMesh(MaterialPtr material);
	virtual ~GLMesh();
	
	virtual void SetupRender(RenderOperation& renderOp, const FrameData& frameData);
	virtual void PostRender(RenderOperation& renderOp, const FrameData& frameData);

private:
    std::shared_ptr<GLRenderer> glRenderer;
};


} // namespace glove