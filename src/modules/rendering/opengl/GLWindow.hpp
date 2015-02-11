#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include <glove/GloveFwd.hpp>
#include <glove/rendering/Rendering.hpp>
#include <glove/rendering/IWindow.hpp>

struct GLFWwindow;

namespace glove {
namespace gl {

/// @ingroup OpenGLRenderer
class GLWindow : public IWindow {
    friend class GlfwWrapper;

  public:
    GLWindow(const EventBusPtr& eventBus, const WindowConstructionHints& creationHints);

    virtual ~GLWindow();

    virtual void MakeCurrent();

    virtual void SetFramebufferSize(int newWidth, int newHeight);

    virtual void SwapBuffers();
    virtual bool CloseRequested() const;
    virtual std::string GetContextVersion() const;
    virtual glm::mat4 GetProjectionMatrix() const;

    virtual ScreenPoint GetPosition() const;
    virtual ScreenDimensions GetDimensions() const;

    virtual void SetPosition(const ScreenPoint& newPosition);
    virtual void SetDimensions(const ScreenDimensions& newDimensions);
    virtual void PollSystemEvents();

    GLFWwindow* GetGlfwWindow() const;
    GLEWContext* GetGlewContext() const;

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