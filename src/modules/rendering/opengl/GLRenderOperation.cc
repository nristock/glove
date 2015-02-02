#include <GL/glew.h>
#include <GL/gl.h>

#include "GLRenderOperation.h"

#include "GLMesh.h"
#include "internal/OpenGLWrapper.h"

#include <glove/rendering/vertex/IIndexData.h>
#include <glove/rendering/vertex/IVertexData.h>

namespace glove {
namespace gl {

GLRenderOperation::GLRenderOperation(bool shouldDelete) : shouldDelete(shouldDelete) {
}

bool GLRenderOperation::ShouldDelete() const {
    return shouldDelete;
}

void GLRenderOperation::Execute(const IRendererPtr& renderer) {
    const GLRenderer* glRenderer = dynamic_cast<const GLRenderer*>(renderer.get());
    ContextId contextId = glRenderer->GetContextId();

    glMesh->EnsureVertexArrayObjectExistsForContext(contextId);
    GL::BindVertexArray(glMesh->GetVertexArrayId(contextId));

    const IIndexDataPtr& indexData = glMesh->GetIndexData();
    const IVertexDataPtr& vertexData = glMesh->GetVertexData();

    if (preRenderCallback) {
//        preRenderCallback(renderer->GetViewProjectionMatrix());
    }
    if (indexData) {
        indexData->BindBuffer();
        GL::DrawElements(GL_TRIANGLES, (GLsizei)indexData->GetIndexCount(), GL_UNSIGNED_INT, 0);
    } else {
        vertexData->BindAllBuffers();
        GL::DrawArrays(GL_TRIANGLES, 0, (GLsizei)vertexData->GetVertexCount());
    }

    if (postRenderCallback) {
        postRenderCallback();
    }
}

void GLRenderOperation::SetMesh(const IMeshPtr& mesh) {
    glMesh = std::dynamic_pointer_cast<GLMesh>(mesh);
}

void GLRenderOperation::SetPreRenderUserCallback(IRenderOperation::PreRenderCallback callback) {
    preRenderCallback = callback;
}

void GLRenderOperation::SetPostRenderUserCallback(IRenderOperation::PostRenderCallback callback) {
    postRenderCallback = callback;
}

}
}