#include <glove/GloveException.h>
#include <glove/rendering/WindowConstructionHints.h>

#include "internal/GlfwWrapper.h"
#include "GLWindow.h"

namespace glove {
namespace gl {

/// @brief The shared wrapper is initialized in subsystem/OpenGLRendererModule.cc LoadExtension making it possible to
///        mock out the actual wrapper when testing.
GlfwWrapperPtr GlfwWrapper::sharedWrapper = GlfwWrapperPtr(new GlfwWrapper());

void GlfwWrapper::InitWrapper() {
    glfwSetErrorCallback(&GlfwWrapper::GlfwErrorSink);

    if (!glfwInit()) {
        throw GLOVE_EXCEPTION("GLFW Initialization failed.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void GlfwWrapper::SetSharedWrapper(const GlfwWrapperPtr& wrapperPtr) {
    sharedWrapper = wrapperPtr;
}

GlfwWrapper::~GlfwWrapper() {
    glfwTerminate();
}

void GlfwWrapper::GlfwErrorSink(int error, const char* description) {
    LOG(sharedWrapper->logger, error, "GLFW Error (" << error << "): " << description);
}

const std::string GlfwWrapper::GetGlfwVersion() {
    return glfwGetVersionString();
}

GLFWwindow* GlfwWrapper::CreateGlfwWindow(const WindowConstructionHints& creationHints, GLWindow* glWindow) {
    GLFWwindow* glfwWindow = glfwCreateWindow(creationHints.GetWidth(), creationHints.GetHeight(),
                                              creationHints.GetTitle().c_str(), nullptr, glfwGetCurrentContext());

    glfwSetWindowUserPointer(glfwWindow, glWindow);
    glfwSetFramebufferSizeCallback(glfwWindow, &GlfwWrapper::GlfwFramebufferSizeChanged);
    glfwSetKeyCallback(glfwWindow, &GlfwWrapper::GlfwKeyEvent);
    glfwSetWindowCloseCallback(glfwWindow, &GlfwWrapper::GlfwCloseEvent);
    glfwSetCursorPosCallback(glfwWindow, &GlfwWrapper::GlfwCursorPositionChanged);
    glfwSetMouseButtonCallback(glfwWindow, &GlfwWrapper::GlfwMouseButtonEvent);

    return glfwWindow;
}

GLWindow* GlfwWrapper::GetGLWindow(GLFWwindow* glfwWindow) {
    return reinterpret_cast<GLWindow*>(glfwGetWindowUserPointer(glfwWindow));
}

void GlfwWrapper::GlfwFramebufferSizeChanged(GLFWwindow* window, int width, int height) {
    GLWindow* gloveWindow = GetGLWindow(window);
    gloveWindow->SetFramebufferSize(width, height);
}

void GlfwWrapper::GlfwKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GLWindow* gloveWindow = GetGLWindow(window);
    gloveWindow->OnKeyEvent(key, scancode, action, mods);
}

void GlfwWrapper::GlfwCloseEvent(GLFWwindow* window) {
    // GLWindow* gloveWindow = GetGLWindow(window);
    // TODO: implement
}

void GlfwWrapper::GlfwCursorPositionChanged(GLFWwindow* window, double x, double y) {
    GLWindow* gloveWindow = GetGLWindow(window);
    gloveWindow->OnMouseMove(x, y);
}

void GlfwWrapper::GlfwMouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {
    GLWindow* gloveWindow = GetGLWindow(window);
    gloveWindow->OnMouseButton(button, action, mods);
}

GLWindow* GlfwWrapper::GetCurrentGLWindow() {
    return GetGLWindow(glfwGetCurrentContext());
}

}
}