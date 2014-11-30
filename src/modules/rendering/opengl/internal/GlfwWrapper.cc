#include "GlfwWrapper.h"

#include <core/GloveException.h>
#include <core/rendering/WindowConstructionHints.h>

#include "../GLWindow.h"

namespace glove {
namespace gl {

struct GlfwWrapperFactory {
    static GlfwWrapper* CreateGlfwWrapper() { return new GlfwWrapper(); }
};

static GlfwWrapper* wrapperInstance = GlfwWrapperFactory::CreateGlfwWrapper();

GlfwWrapper::GlfwWrapper() {
    glfwSetErrorCallback(&GlfwWrapper::GlfwErrorSink);

    if (!glfwInit()) {
        throw GLOVE_EXCEPTION("GLFW Initialization failed.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

GlfwWrapper::~GlfwWrapper() {
    glfwTerminate();
}

void GlfwWrapper::GlfwErrorSink(int error, const char* description) {
    LOG(wrapperInstance->logger, error, "GLFW Error (" << error << "): " << description);
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