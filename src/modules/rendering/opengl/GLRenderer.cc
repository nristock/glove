#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/format.hpp>

#include "glove/GloveCore.hpp"
#include "glove/GloveException.hpp"
#include "glove/graph/Scenegraph.hpp"
#include "glove/rendering/gamecomponent/CameraBase.hpp"
#include "glove/rendering/Rendering.hpp"
#include "glove/rendering/target/IRenderTarget.hpp"
#include "glove/rendering/buffers/IGpuBuffer.hpp"
#include "glove/rendering/mesh/IMesh.hpp"
#include "glove/rendering/WindowConstructionHints.hpp"
#include "glove/rendering/vertex/IVertexData.hpp"
#include "glove/rendering/vertex/IIndexData.hpp"
#include "glove/rendering/RenderState.hpp"

#include "GLRenderer.hpp"
#include "GLMesh.hpp"
#include "GLRenderOperation.hpp"
#include "internal/OpenGLWrapper.hpp"
#include "internal/GlfwWrapper.hpp"
#include "target/GLRenderTarget.hpp"
#include "target/GLDefaultRenderTarget.hpp"

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