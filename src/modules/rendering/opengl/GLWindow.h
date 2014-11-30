#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include <core/GloveFwd.h>

#include <core/rendering/Rendering.h>
#include <core/rendering/IWindow.h>

struct GLFWwindow;

namespace glove {
namespace gl {

/// @ingroup OpenGLRenderer
class GLWindow : public IWindow {
    friend class GlfwWrapper;

  public:
    GLWindow(const EventBusPtr& eventBus, const WindowConstructionHints& creationHints);

    virtual ~GLWindow();

    virtual GLOVE_INLINE void MakeCurrent();

    virtual GLOVE_INLINE void SetFramebufferSize(int newWidth, int newHeight);

    virtual GLOVE_INLINE void SwapBuffers();
    virtual GLOVE_INLINE bool CloseRequested() const;
    virtual GLOVE_INLINE std::string GetContextVersion() const;
    virtual GLOVE_INLINE glm::mat4 GetProjectionMatrix() const;

    virtual GLOVE_INLINE ScreenPoint GetPosition() const;
    virtual GLOVE_INLINE ScreenDimensions GetDimensions() const;

    virtual GLOVE_INLINE void SetPosition(const ScreenPoint& newPosition);
    virtual GLOVE_INLINE void SetDimensions(const ScreenDimensions& newDimensions);
    virtual GLOVE_INLINE void PollSystemEvents();

    GLOVE_INLINE GLFWwindow* GetGlfwWindow() const;
    GLOVE_INLINE GLEWContext* GetGlewContext() const;

  private:
    GLFWwindow* glfwWindow;
    GLEWContext* glewContext;

    EventBusPtr eventBus;

    int viewportWidth, viewportHeight;
    float aspectRatio;
    float orthoSize;
    glm::mat4 projectionMat;

    void OnKeyEvent(int key, int scancode, int action, int mods);
    void OnMouseMove(double x, double y);
    void OnMouseButton(int button, int action, int mods);

    void SetupViewport();
};

}
} // namespace glove