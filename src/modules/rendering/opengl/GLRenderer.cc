#include "GLRenderer.h"

#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/format.hpp>

#include "core/GloveCore.h"
#include "core/GloveException.h"
#include <core/graph/Scenegraph.h>
#include <core/graph/Camera.h>

#include <core/rendering/Rendering.h>
#include <core/rendering/IRenderable.h>
#include <core/rendering/buffers/IGpuBuffer.h>
#include <core/rendering/mesh/IMesh.h>
#include <core/rendering/WindowConstructionHints.h>
#include <core/rendering/vertex/IVertexData.h>
#include <core/rendering/vertex/IIndexData.h>

#include "GLBaseMesh.h"
#include "internal/GlfwWrapper.h"

GLEWContext* glewGetContext();

namespace glove {
namespace gl {

GLRenderer::GLRenderer(const EventBusPtr& eventBus, const WindowConstructionHints& windowCreationHints,
                       const ContextId contextId)
    : eventBus(eventBus), contextId(contextId) {
    currentRenderOperation.Reset();

    CreateWindow(windowCreationHints);
}

void GLRenderer::RenderScene(ScenegraphPointer scenegraph, FrameData& frameData) {
    frameData.viewProjectionMatrix = window->GetProjectionMatrix() * scenegraph->GetMainCamera()->GetViewMatrix();

    scenegraph->IterateGameObjects([&](GameObjectPtr gameObject) {
        gameObject->IterateRenderableComponents([&](const IRenderablePtr& renderable) {
            renderable->SetupRender(currentRenderOperation, frameData);

            GLBaseMeshPtr baseMesh = std::dynamic_pointer_cast<GLBaseMesh>(renderable);
            RenderObject(currentRenderOperation, frameData, baseMesh);
            renderable->PostRender(currentRenderOperation, frameData);
        });
    });
}

void GLRenderer::RenderObject(RenderOperation& renderOp, const FrameData& frameData, const GLBaseMeshPtr& baseMesh) {
    baseMesh->EnsureVertexArrayObjectExistsForContext(contextId);
    GL::BindVertexArray(baseMesh->GetVertexArrayId(contextId));

    if (renderOp.indexData == nullptr) {
        renderOp.vertexData->BindAllBuffers();
        GL::DrawArrays(GL_TRIANGLES, 0, (GLsizei)renderOp.vertexData->GetVertexCount());
    } else {
        renderOp.indexData->BindBuffer();
        GL::DrawElements(GL_TRIANGLES, (GLsizei)renderOp.indexData->GetIndexCount(), GL_UNSIGNED_INT, 0);
    }
}

void GLRenderer::ClearBuffers() {
    GL::Clear(GL_COLOR_BUFFER_BIT);
}

void GLRenderer::SwapBuffers() {
    window->SwapBuffers();
}

void GLRenderer::CreateWindow(const WindowConstructionHints& windowCreationHints) {
    window = std::make_shared<GLWindow>(eventBus, windowCreationHints);

    window->MakeCurrent();

    glewExperimental = GL_TRUE;
    GLenum glewInitRes = glewInit();
    if (glewInitRes != GLEW_OK) {
        throw GLOVE_EXCEPTION(std::string((char*)glewGetErrorString(glewInitRes)));
    }

    LOG(logger, info, (boost::format("Created Window (%1%)") % window->GetContextVersion()).str());
}

IWindowPtr GLRenderer::GetAssociatedWindow() {
    return window;
}

}
} /* namespace glove */

GLEWContext* glewGetContext() {
    return glove::gl::GlfwWrapper::GetCurrentGLWindow()->GetGlewContext();
}