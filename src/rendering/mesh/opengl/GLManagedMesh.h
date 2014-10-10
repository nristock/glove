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
		glGenVertexArrays(1, &vertexArrayId);
	}

	virtual ~GLManagedMesh() {
		glBindVertexArray(vertexArrayId);

		for (auto vertexAttribute : this->GetVertexData()->GetVertexLayout()->GetAttributes()) {
			GPUBufferPtr gpuBuffer = this->GetVertexData()->GetBuffer(vertexAttribute.GetBindingSlot());
			gpuBuffer->Bind();

			GLuint attribIndex = this->GetShader()->GetVertexAttributePosition(vertexAttribute.GetSemantic());
			if (attribIndex < 0) {
				continue;
			}

			glDisableVertexAttribArray(attribIndex);
		}

		glDeleteVertexArrays(1, &vertexArrayId);
		vertexArrayId = 0;
	}

	virtual void SetupRender(RenderOperation& renderOp, const FrameData& frameData) {
		ManagedMesh<VertexLayoutType>::SetupRender(renderOp, frameData);

		glBindVertexArray(GetVertexArrayId());
	}

	virtual void PostRender(RenderOperation& renderOp, const FrameData& frameData) {}
};


} // namespace glove

#endif