#include "GLMesh.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include "core/GloveCore.h"
#include "core/IRenderer.h"

#include "buffers/IGpuBuffer.h"

#include "rendering/vertex/VertexData.h"
#include "rendering/vertex/VertexLayout.h"
#include "rendering/FrameData.h"

#include "shader/ShaderProgram.h"

GLEWContext* glewGetContext();

namespace glove {

GLMesh::GLMesh(const RendererPtr& renderer, const GpuBufferManagerPtr gpuBufferManager, MaterialPtr material) : Mesh(renderer, gpuBufferManager, material), EnableProfilable() {

    glRenderer = std::dynamic_pointer_cast<GLRenderer>(renderer);
}

GLMesh::~GLMesh() {
    for (auto vertexArrayIdEntry : vertexArrayIds) {
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