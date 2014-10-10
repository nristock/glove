#include "GLMesh.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include "buffers/GPUBuffer.h"

#include "rendering/vertex/VertexData.h"
#include "rendering/vertex/VertexLayout.h"

#include "shader/ShaderProgram.h"

namespace glove {
	
GLMesh::GLMesh(MaterialPtr material) : Mesh(material) {	
	glGenVertexArrays(1, &vertexArrayId);
}

GLMesh::~GLMesh() {	
	glBindVertexArray(vertexArrayId);

	for (auto vertexAttribute : GetVertexData()->GetVertexLayout()->GetAttributes()) {
		GPUBufferPtr gpuBuffer = GetVertexData()->GetBuffer(vertexAttribute.GetBindingSlot());
		gpuBuffer->Bind();

		GLuint attribIndex = GetShader()->GetVertexAttributePosition(vertexAttribute.GetSemantic());
		if (attribIndex < 0) {
			continue;
		}

		glDisableVertexAttribArray(attribIndex);
	}

	glDeleteVertexArrays(1, &vertexArrayId);
	vertexArrayId = 0;
}

void GLMesh::SetupRender(RenderOperation& renderOp, const FrameData& frameData) {
	Mesh::SetupRender(renderOp, frameData);
	
	glBindVertexArray(GetVertexArrayId());
}

void GLMesh::PostRender(RenderOperation& renderOp, const FrameData& frameData) {

}

} // namespace glove