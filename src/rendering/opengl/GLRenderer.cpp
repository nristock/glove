#include "GLRenderer.h"

#include <sstream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/format.hpp>

#include "core/GloveCore.h"
#include "core/GloveException.h"
#include "graph/Scenegraph.h"
#include "rendering/Camera.h"
#include "rendering/IRenderable.h"
#include "rendering/FrameData.h"
#include "log/Log.h"
#include "GLWindow.h"

#include "buffers/GPUBuffer.h"
#include "rendering/vertex/IndexData.h"
#include "rendering/vertex/VertexData.h"
#include "rendering/vertex/VertexLayout.h"
#include "rendering/mesh/IMesh.h"
#include "rendering/mesh/opengl/GLBaseMesh.h"
#include "shader/ShaderProgram.h"
#include "shader/Material.h"

GLEWContext* glewGetContext();

namespace glove {

GLRenderer* rendererInstance = nullptr;

GLRenderer::GLRenderer() {
    currentRenderOperation.Reset();
}

GLRenderer::~GLRenderer() {
}

void GLRenderer::Init() {
    rendererInstance = this;

    glfwSetErrorCallback(&GLRenderer::GlfwErrorSink);

    if (!glfwInit()) {
        throw GloveException("GLFW Initialization failed.");
    }

    OLOG(info, "Glove renderer initialized");
}

void GLRenderer::Exit() {
    glfwTerminate();
}

void GLRenderer::GlfwErrorSink(int error, const char* description) {
    LOG(logging::globalLogger, error, "GLFW Error (" << error << "): " << description);
}

void GLRenderer::RenderScene(ScenegraphPointer scenegraph, FrameData& frameData) {
    frameData.currentContext = currentContextId;
    frameData.viewProjectionMatrix = activeWindow->GetProjMatrix() * scenegraph->GetMainCamera()->GetViewMatrix();

    scenegraph->IterateGameObjects([&](GameObjectPtr gameObject) {
        gameObject->IterateRenderableComponents([&](const IRenderablePtr& renderable) {
            renderable->SetupRender(currentRenderOperation, frameData);
            RenderObject(currentRenderOperation, frameData, gameObject);
            renderable->PostRender(currentRenderOperation, frameData);
        });
    });
}

void GLRenderer::RenderObject(RenderOperation& renderOp, const FrameData& frameData, const GameObjectPtr& gameObject) {
    glm::mat4 mvpMatrix = gameObject->GetTransform().GetGlobalTransform() * frameData.viewProjectionMatrix;
    renderOp.material->SetMaterialAttribute(MMA_MAT_MVP, mvpMatrix);

    if (renderOp.indexData == nullptr) {
        glDrawArrays(GL_TRIANGLES, 0, renderOp.vertexData->GetVertexCount());
    }
    else {
        renderOp.indexData->GetBuffer()->Bind();
        glDrawElements(GL_TRIANGLES, renderOp.indexData->GetIndexCount(), GL_UNSIGNED_INT, 0);
    }
}

void GLRenderer::CreateVertexAttributeMappings(IMesh* mesh) {
    GLBaseMesh* oglMesh = dynamic_cast<GLBaseMesh*>(mesh);
    VertexDataPtr vertexData = mesh->GetVertexData();
    ShaderProgramPtr shader = mesh->GetShader();

    for (size_t i = 0; i < GetWindowCount(); ++i) {
        SetActiveWindow(i);

        glBindVertexArray(oglMesh->GetVertexArrayId(i));

        size_t stride = 0;
        for (auto vertexAttribute : vertexData->GetVertexLayout()->GetAttributes()) {
            stride += vertexAttribute.GetSize();
        }

        for (auto vertexAttribute : vertexData->GetVertexLayout()->GetAttributes()) {
            GPUBufferPtr gpuBuffer = vertexData->GetBuffer(vertexAttribute.GetBindingSlot());
            gpuBuffer->Bind();

            GLuint attribIndex = shader->GetVertexAttributePosition(vertexAttribute.GetSemantic());
            if (attribIndex < 0) {
                OLOG(error, "Vertex attribute in buffer not mapped to shader attribute index.");
                continue;
            }

            glVertexAttribPointer(
                    attribIndex,
                    vertexAttribute.GetNumberOfComponents(),
                    TranslateVertexAttributeType(vertexAttribute.GetType()),
                    GL_FALSE,
                    stride,
                    (void*) vertexAttribute.GetOffset());
            glEnableVertexAttribArray(attribIndex);
        }
    }
}

GLenum GLRenderer::TranslateVertexAttributeType(VertexAttributeType attribType) {
    switch (attribType) {
        case VAT_FLOAT3:
        case VAT_FLOAT4:
            return GL_FLOAT;
    }

    throw GLOVE_EXCEPTION("Invalid VertexAttributeType");
}

void GLRenderer::ClearBuffers() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLRenderer::SwapBuffers() {
    activeWindow->SwapBuffers();
}

WindowPtr GLRenderer::CreateWindow(int windowWidth, int windowHeight, int contextVersionMajor, int contextVersionMinor) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextVersionMinor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    WindowPtr window;

    window = WindowPtr(activeWindow ? new GLWindow(windowWidth, windowHeight, activeWindow) : new GLWindow(windowWidth, windowHeight));

    windows.push_back(WindowGlewContextPair(window, new GLEWContext()));

    if (!activeWindow) {
        activeWindow = window;
    }

    WindowPtr currentlyActiveWindow = activeWindow;
    SetActiveWindow(GetWindowCount() - 1);

    glewExperimental = GL_TRUE;
    GLenum glewInitRes = glewInit();
    if (glewInitRes != GLEW_OK) {
        throw GLOVE_EXCEPTION(std::string((char*) glewGetErrorString(glewInitRes)));
    }

    OLOG(info, (boost::format("Created Window (%1%)") % window->GetContextVersion()).str());

    if (currentlyActiveWindow != window) {
        for (unsigned short i = 0; i < GetWindowCount(); ++i) {
            if (windows[i].first == currentlyActiveWindow) {
                SetActiveWindow(i);
                break;
            }
        }
    }

    return window;
}

GLuint GLRenderer::GenerateVertexArray(size_t contextId) {
    size_t prevContextId = currentContextId;

    if (currentContextId != contextId) {
        SetActiveWindow(contextId);
    }

    GLuint temporaryId;
    glGenVertexArrays(1, &temporaryId);

    if (prevContextId != contextId) {
        SetActiveWindow(prevContextId);
    }

    return temporaryId;
}

GLuint GLRenderer::DestroyVertexArray(size_t contextId, GLuint vertexArrayId) {
    size_t prevContextId;

    if (currentContextId != contextId) {
        prevContextId = currentContextId;
        SetActiveWindow(contextId);
    }

    glDeleteVertexArrays(1, &vertexArrayId);

    if (prevContextId != contextId) {
        SetActiveWindow(prevContextId);
    }
}

void GLRenderer::PollSystemEvents() {
    glfwPollEvents();
}
}

/* namespace glove */

GLEWContext* glewGetContext() {
    return glove::rendererInstance->GetCurrentGLEWContext();
}