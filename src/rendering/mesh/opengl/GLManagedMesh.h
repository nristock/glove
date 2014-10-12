#ifndef RENDERING_MESH_OPENGL_GLMANAGEDMESH_H_
#define RENDERING_MESH_OPENGL_GLMANAGEDMESH_H_

#include <GL/glew.h>
#include <GL/gl.h>

#include "rendering/mesh/ManagedMesh.h"
#include "rendering/mesh/opengl/GLBaseMesh.h"

namespace glove {

template<class VertexLayoutType> class GLManagedMesh : public ManagedMesh<VertexLayoutType>, public GLBaseMesh {
	GLOVE_MEM_ALLOC_FUNCS("GLManagedMesh")
public:
	GLManagedMesh(MaterialPtr material) : ManagedMesh<VertexLayoutType>(material) {
        glRenderer = std::dynamic_pointer_cast<GLRenderer>(this->gloveCore->GetRenderer());
	}

	virtual ~GLManagedMesh() {
        for(auto vertexArrayIdEntry : vertexArrayIds) {
            glRenderer->DestroyVertexArray(vertexArrayIdEntry.first, vertexArrayIdEntry.second);
        }
	}

	virtual void SetupRender(RenderOperation& renderOp, const FrameData& frameData) {
        glGetError();

		ManagedMesh<VertexLayoutType>::SetupRender(renderOp, frameData);

		glBindVertexArray(GetVertexArrayId(frameData.currentContext));

        GLenum error = glGetError();
        if(error != GL_NO_ERROR) {
            OLOG(error, error);
        }
	}

	virtual void PostRender(RenderOperation& renderOp, const FrameData& frameData) {}

private:
    std::shared_ptr<GLRenderer> glRenderer;
};


} // namespace glove

#endif