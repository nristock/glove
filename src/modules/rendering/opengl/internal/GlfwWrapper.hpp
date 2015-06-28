#pragma once

#include <mutex>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <glove/log/Log.hpp>
#include <glove/input/Keys.hpp>
#include <glove/math/IntPoint.hpp>

#include "subsystem/OpenGLRendererModule.hpp"

using namespace BlueDwarf;

namespace BlueDwarf {
namespace gl {

/// @ingroup Internal
class GlfwWrapper {
  public:
    GlfwWrapper() = default;
    GlfwWrapper(const GlfwWrapper&) = delete;
    GlfwWrapper& operator=(const GlfwWrapper&) = delete;

    virtual ~GlfwWrapper();

    static void SetSharedWrapper(const GlfwWrapperPtr& wrapperPtr);

    static const std::string GetGlfwVersion();
    static GLFWwindow* CreateGlfwWindow(const IntPoint& position, const IntPoint& size,
                                        const std::string& title, GLWindow* glWindow);
    static GLWindow* GetCurrentGLWindow();

    static const Key& ConvertKeyCode(int glfwKeyCode);

    static void InitWrapper();

  private:
    Logger logger;

    static GlfwWrapperPtr sharedWrapper;

    static GLWindow* GetGLWindow(GLFWwindow* glfwWindow);

    // General Callbacks
    static void GlfwErrorSink(int error, const char* description);

    // Window Callbacks
    static void GlfwFramebufferSizeChanged(GLFWwindow* window, int width, int height);
    static void GlfwKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void GlfwCloseEvent(GLFWwindow* window);
    static void GlfwCursorPositionChanged(GLFWwindow* window, double x, double y);
    static void GlfwMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
};
}
} /* namespace BlueDwarf */