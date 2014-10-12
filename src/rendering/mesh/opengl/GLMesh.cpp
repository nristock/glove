#include "GLMesh.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include "core/GloveCore.h"
#include "core/IRenderer.h"

#include "buffers/GPUBuffer.h"

#include "rendering/vertex/VertexData.h"
#include "rendering/vertex/VertexLayout.h"
#include "rendering/FrameData.h"

#include "shader/ShaderProgram.h"

namespace glove {
	
GLMesh::GLMesh(MaterialPtr material) : Mesh(material) {
    glRenderer = std::dynamic_pointer_cast<GLRenderer>(gloveCore->GetRenderer());
}

GLMesh::~GLMesh() {
    for(auto vertexArrayIdEntry : vertexArrayIds) {
        glRenderer->DestroyVertexArray(vertexArrayIdEntry.first, vertexArrayIdEntry.second);
    }
}

void GLMesh::SetupRender(RenderOperation& renderOp, const FrameData& frameData) {
	Mesh::SetupRender(renderOp, frameData);
	
	glBindVertexArray(GetVertexArrayId(frameData.currentContext));
}

void GLMesh::PostRender(RenderOperation& renderOp, const FrameData& frameData) {

}

} // namespace glove