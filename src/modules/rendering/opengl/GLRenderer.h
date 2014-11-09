#pragma once

#include <mutex>
#include <vector>
#include <utility>

#include <GL/glew.h>
#include <GL/gl.h>
#include <log/Log.h>

#include "core/GloveException.h"
#include "core/GloveFwd.h"
#include "core/RenderOperation.h"
#include "core/IRenderer.h"

#include "rendering/FrameData.h"
#include "rendering/vertex/VertexAttributeType.h"
#include "GLWindow.h"

struct GLFWwindow;

namespace glove {

class GLRenderer : public IRenderer {
Profilable()
public:
    typedef std::pair<WindowPtr, GLEWContext*> WindowGlewContextPair;
    typedef std::vector<WindowGlewContextPair> WindowList;

	GLRenderer(const EventBusPtr& eventBus);

    virtual ~GLRenderer();

    virtual void Init();

    virtual void Exit();

    virtual WindowPtr CreateRenderWindow(int windowWidth, int windowHeight, int contextVersionMajor, int contextVersionMinor);

    virtual void ClearBuffers();

    virtual void RenderScene(ScenegraphPointer scenegraph, FrameData& frameData);

    virtual void SwapBuffers();

    virtual WindowPtr GetActiveWindow() const {
        return activeWindow;
    }

    virtual void SetActiveWindow(unsigned short id) {
        if (id >= windows.size())
            throw GLOVE_EXCEPTION("Window index is out of range.");

        activeWindow = windows[id].first;
        activeGlewContext = windows[id].second;
        currentContextId = id;

        activeWindow->MakeCurrent();
        glClearColor(id, id, id, 1);
    }

    virtual size_t GetWindowCount() const {
        return windows.size();
    }

    virtual void CreateVertexAttributeMappings(IMesh* mesh);

    virtual void PollSystemEvents();

    // OpenGL specific
    GLEWContext* GetCurrentGLEWContext() const {
        return activeGlewContext;
    };

    GLuint GenerateVertexArray(size_t contextId);

    void DestroyVertexArray(size_t contextId, GLuint vertexArrayId);

private:
    logging::GloveLogger logger;
    EventBusPtr eventBus;

    WindowList windows;

    WindowPtr activeWindow;
    GLEWContext* activeGlewContext;
    size_t currentContextId;

    RenderOperation currentRenderOperation;

    static void GlfwErrorSink(int error, const char* description);

    void RenderObject(RenderOperation& renderOp, const FrameData& frameData, const GameObjectPtr& gameObject);

    GLenum TranslateVertexAttributeType(VertexAttributeType attribType);
};

} /* namespace glove */
