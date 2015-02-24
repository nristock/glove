#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/format.hpp>

#include <glove/rendering/WindowConstructionHints.hpp>

#include "GLWindow.hpp"
#include "internal/GlfwWrapper.hpp"

namespace glove {
namespace gl {

GLWindow::GLWindow(const WindowConstructionHints& creationHints)
    : viewportWidth(0), viewportHeight(0), aspectRatio(0), orthoSize(10) {
    glfwWindow = GlfwWrapper::CreateGlfwWindow(creationHints, this);
    glewContext = new GLEWContext();

    SetupViewport();
}

void GLWindow::SetupViewport() {
    int width, height;
    glfwGetFramebufferSize(glfwWindow, &width, &height);
    SetFramebufferSize(width, height);
}

GLWindow::~GLWindow() {
    glfwDestroyWindow(glfwWindow);
}

void GLWindow::MakeCurrent() {
    glfwMakeContextCurrent(glfwWindow);
}

bool GLWindow::CloseRequested() const {
    return glfwWindowShouldClose(glfwWindow) != 0;
}

void GLWindow::SetFramebufferSize(int width, int height) {
    viewportWidth = width;
    viewportHeight = height;

    GLFWwindow* currentContext = glfwGetCurrentContext();
    if (currentContext != glfwWindow) {
        MakeCurrent();
    }

    glViewport(0, 0, width, height);

    if (currentContext != glfwWindow) {
        glfwMakeContextCurrent(currentContext);
    }

    aspectRatio = width / height;
    projectionMat = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio);
}

void GLWindow::SwapBuffers() {
    glfwSwapBuffers(glfwWindow);
}

void GLWindow::OnKeyEvent(int key, int scancode, int action, int mods) {
    const Key& gloveKey = GlfwWrapper::ConvertKeyCode(key);
    KeyState newState(action == GLFW_PRESS);

    gloveKey.UpdateState(newState);
}

void GLWindow::OnMouseMove(double x, double y) {
    static double oldX = x;
    static double oldY = y;

    double deltaX = x - oldX;
    double deltaY = y - oldY;

    if(std::abs(deltaX) > 0.01f) {
        KeyState newState(static_cast<float>(x));
        Keys::MouseX.UpdateState(newState);
    }

    if(std::abs(deltaY) > 0.01f) {
        KeyState newState(static_cast<float>(y));
        Keys::MouseY.UpdateState(newState);
    }
}

void GLWindow::OnMouseButton(int button, int action, int mods) {
    const Key& gloveKey = GlfwWrapper::ConvertKeyCode(button);
    KeyState newState(action == GLFW_PRESS);

    gloveKey.UpdateState(newState);
}

std::string GLWindow::GetContextVersion() const {
    return (boost::format("OpenGL %1%.%2%.%3%") % glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_VERSION_MAJOR) %
            glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_VERSION_MINOR) %
            glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_REVISION)).str();
}

GLFWwindow* GLWindow::GetGlfwWindow() const {
    return glfwWindow;
}

glm::mat4 GLWindow::GetProjectionMatrix() const {
    return projectionMat;
}

GLEWContext* GLWindow::GetGlewContext() const {
    return glewContext;
}

ScreenPoint GLWindow::GetPosition() const {
    ScreenPoint position;
    glfwGetWindowPos(glfwWindow, &position.x, &position.y);

    return position;
}

ScreenDimensions GLWindow::GetDimensions() const {
    int x, y;
    glfwGetWindowSize(glfwWindow, &x, &y);

    return ScreenDimensions(x, y);
}

void GLWindow::SetPosition(const ScreenPoint& newPosition) {
    glfwSetWindowPos(glfwWindow, newPosition.x, newPosition.y);
}

void GLWindow::SetDimensions(const ScreenDimensions& newDimensions) {
    glfwSetWindowSize(glfwWindow, static_cast<int>(newDimensions.GetWidth()), static_cast<int>(newDimensions.GetHeight()));
}

void GLWindow::PollSystemEvents() {
    glfwPollEvents();
}
}
} // namespace glove