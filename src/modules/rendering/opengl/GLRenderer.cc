#include "GLRenderer.h"

#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/format.hpp>

#include "core/GloveCore.h"
#include "core/GloveException.h"
#include <core/graph/Scenegraph.h>
#include <core/graph/gamecomponent/CameraBase.h>

#include <core/rendering/Rendering.h>
#include <core/rendering/target/IRenderTarget.h>
#include <core/rendering/buffers/IGpuBuffer.h>
#include <core/rendering/mesh/IMesh.h>
#include <core/rendering/WindowConstructionHints.h>
#include <core/rendering/vertex/IVertexData.h>
#include <core/rendering/vertex/IIndexData.h>
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

RenderTargetHandle GLRenderer::CreateRenderTarget() {
    throw GLOVE_EXCEPTION("Not implemented");
    //return std::make_shared<GLRenderTarget>()
}

void GLRenderer::MapCameraToTarget(const CameraBaseHandle& camera, const RenderTargetHandle& renderTarget) {
    const Dimensions& targetDimensions = renderTarget->GetDimensions();
    camera->SetAspectRatio(targetDimensions.GetAspectRatio());
}

void GLRenderer::RenderScene(const ScenegraphHandle& scenegraph) {
    std::queue<IRenderOperation*> renderQueue;

    scenegraph->IterateGameObjects([&](const GameObjectHandle& gameObject) {
        gameObject->IterateComponents([&](const GameComponentHandle& component) {
            component.lock()->QueueRenderOperation(renderQueue);
        });
    });

    while(!renderQueue.empty()) {
        IRenderOperation* renderOp = renderQueue.front();
        renderQueue.pop();

        renderOp->Execute(shared_from_this());
        if (renderOp->ShouldDelete()) {
            delete renderOp;
        }
    }
}

RenderTargetHandle GLRenderer::GetDefaultRenderTarget() {
    return defaultRenderTarget;
}
}
} /* namespace glove */

GLEWContext* glewGetContext() {
    return glove::gl::GlfwWrapper::GetCurrentGLWindow()->GetGlewContext();
}