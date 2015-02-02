#include "GLRenderer.h"

#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/format.hpp>

#include <glove/GloveCore.h>
#include <glove/GloveException.h>
#include <glove/graph/Scenegraph.h>
#include <glove/rendering/gamecomponent/CameraBase.h>
#include <glove/rendering/Rendering.h>
#include <glove/rendering/target/IRenderTarget.h>
#include <glove/rendering/buffers/IGpuBuffer.h>
#include <glove/rendering/mesh/IMesh.h>
#include <glove/rendering/WindowConstructionHints.h>
#include <glove/rendering/vertex/IVertexData.h>
#include <glove/rendering/vertex/IIndexData.h>
#include <glove/rendering/RenderState.h>

#include <modules/rendering/opengl/target/GLRenderTarget.h>
#include <modules/rendering/opengl/target/GLDefaultRenderTarget.h>

#include "internal/GlfwWrapper.h"
#include "internal/OpenGLWrapper.h"
#include "GLMesh.h"
#include "GLRenderOperation.h"

GLEWContext* glewGetContext();

namespace glove {
namespace gl {

GLRenderer::GLRenderer(const EventBusPtr& eventBus, const WindowConstructionHints& windowCreationHints,
                       const ContextId contextId)
    : eventBus(eventBus), contextId(contextId) {
    CreateWindow(windowCreationHints);
    defaultRenderTarget = std::make_shared<GLDefaultRenderTarget>(window->GetDimensions());
}

void GLRenderer::RenderObject(RenderOperation& renderOp, const FrameData& frameData, const GLMeshPtr& baseMesh) {
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

ContextId GLRenderer::GetContextId() const {
    return contextId;
}

RenderTargetHandle GLRenderer::CreateRenderTarget(const ScreenDimensions& dimensions) {
    return std::make_shared<GLRenderTarget>(dimensions);
}

RenderTargetHandle GLRenderer::GetDefaultRenderTarget() {
    return defaultRenderTarget;
}


}
} /* namespace glove */

GLEWContext* glewGetContext() {
    return glove::gl::GlfwWrapper::GetCurrentGLWindow()->GetGlewContext();
}