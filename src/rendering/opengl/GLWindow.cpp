#include "GLWindow.h"

#include "core/GloveCore.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <boost/format.hpp>

#include "event/EventBus.h"
#include "event/type/KeyEvent.h"
#include "event/type/MouseButtonEvent.h"
#include "event/type/MouseMoveEvent.h"

namespace glove {

GLWindow::GLWindow(int width, int height) : GLWindow(width, height, nullptr) {
}

GLWindow::GLWindow(int width, int height, WindowPtr parent) : viewportWidth(0), viewportHeight(0), aspectRatio(0), orthoSize(10) {
    this->parent = parent ? std::dynamic_pointer_cast<GLWindow>(parent)->GetGlfwWindow() : nullptr;

    glfwWindow = glfwCreateWindow(width, height, "glove", NULL, this->parent);
    glfwSetWindowUserPointer(glfwWindow, this);
    glfwSetFramebufferSizeCallback(glfwWindow, &GLWindow::GlfwFramebufferSizeChanged);
    glfwSetKeyCallback(glfwWindow, &GLWindow::GlfwKeyEvent);
    glfwSetWindowCloseCallback(glfwWindow, &GLWindow::GlfwCloseEvent);
    glfwSetCursorPosCallback(glfwWindow, &GLWindow::GlfwCursorPositionChanged);
    glfwSetMouseButtonCallback(glfwWindow, &GLWindow::GlfwMouseButtonEvent);

    glfwGetFramebufferSize(glfwWindow, &width, &height);
    SetFramebuffer(width, height);
}

GLWindow::~GLWindow() {
	glfwDestroyWindow(glfwWindow);
}

void GLWindow::MakeCurrent() {
	glfwMakeContextCurrent(glfwWindow);
}

bool GLWindow::CloseRequested() const {
	return glfwWindowShouldClose(glfwWindow);
}

void GLWindow::SetFramebuffer(int width, int height) {
	viewportWidth = width;
	viewportHeight = height;

    //TODO: Remove switching overhead
    GLFWwindow* currentContext = glfwGetCurrentContext();
    MakeCurrent();
    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(currentContext);

	aspectRatio = width / height;
	projectionMat = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio);
}

void GLWindow::SwapBuffers() {
	glfwSwapBuffers(glfwWindow);
}

void GLWindow::OnKeyEvent(int key, int scancode, int action, int mods) {
	KeyAction keyAction = (action == GLFW_PRESS) ? KA_PRESS : ((action == GLFW_RELEASE) ? KA_RELEASE : KA_REPEAT);
	KeyEvent keyEvent((KeyCode)key, keyAction, mods & GLFW_MOD_ALT, mods & GLFW_MOD_CONTROL, mods & GLFW_MOD_SHIFT, mods & GLFW_MOD_SUPER);
	gloveCore->GetEventBusRef()->Publish(keyEvent);
}

void GLWindow::GlfwFramebufferSizeChanged(GLFWwindow* window, int width, int height) {
	GLWindow* gloveWindow = reinterpret_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	gloveWindow->SetFramebuffer(width, height);
}

void GLWindow::GlfwKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	GLWindow* gloveWindow = reinterpret_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	gloveWindow->OnKeyEvent(key, scancode, action, mods);
}

void GLWindow::OnMouseMove(double x, double y) {
    MouseMoveEvent moveEvent(x, y);
    gloveCore->GetEventBusRef()->Publish(moveEvent);
}

void GLWindow::OnMouseButton(int button, int action, int mods) {
    ButtonAction buttonAction = (action == GLFW_PRESS) ? BA_PRESS : BA_RELEASE;
    MouseButtonEvent buttonEvent((MouseButton)button, buttonAction, mods & GLFW_MOD_ALT, mods & GLFW_MOD_CONTROL, mods & GLFW_MOD_SHIFT, mods & GLFW_MOD_SUPER);
    gloveCore->GetEventBusRef()->Publish(buttonEvent);
}

void GLWindow::GlfwCursorPositionChanged(GLFWwindow* window, double x, double y) {
    GLWindow* gloveWindow = reinterpret_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    gloveWindow->OnMouseMove(x, y);
}

void GLWindow::GlfwMouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {
    GLWindow* gloveWindow = reinterpret_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    gloveWindow->OnMouseButton(button, action, mods);
}

void GLWindow::GlfwCloseEvent(GLFWwindow *window) {
    //TODO: Schedule window close
}

std::string GLWindow::GetContextVersion() const {
    return (boost::format("OpenGL %1%.%2%.%3%")
            % glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_VERSION_MAJOR)
            % glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_VERSION_MINOR)
            % glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_REVISION)).str();
}
} // namespace glove