#pragma once

#include <mutex>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <glove/log/Log.hpp>
#include <glove/rendering/Rendering.hpp>

#include "subsystem/OpenGLRendererModule.hpp"

namespace glove {
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
    static GLFWwindow* CreateGlfwWindow(const WindowConstructionHints& creationHints, GLWindow* glWindow);
    static GLWindow* GetCurrentGLWindow();

    static void InitWrapper();

  private:
    logging::GloveLogger logger;

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
} /* namespace glove */