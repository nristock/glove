#include "GloveWindow.h"

#include "core/GloveCore.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <boost/format.hpp>

#include "event/EventBus.h"
#include "event/type/KeyEvent.h"

namespace glove {

GloveWindow::GloveWindow() : orthoSize(10), viewportWidth(0), viewportHeight(0), aspectRatio(0) {
    this->parent = nullptr;
}

GloveWindow::GloveWindow(GloveWindowPtr parent) : orthoSize(10), viewportWidth(0), viewportHeight(0), aspectRatio(0) {
    this->parent = parent->GetGlfwWindow();
}

void GloveWindow::Init(int width, int height) {
    glfwWindow = glfwCreateWindow(width, height, "glove", NULL, parent);
	glfwSetWindowUserPointer(glfwWindow, this);
	glfwSetFramebufferSizeCallback(glfwWindow, &GloveWindow::GlfwFramebufferSizeChanged);
	glfwSetKeyCallback(glfwWindow, &GloveWindow::GlfwKeyEvent);
    glfwSetWindowCloseCallback(glfwWindow, &GloveWindow::GlfwCloseEvent);

	glfwGetFramebufferSize(glfwWindow, &width, &height);
	SetFramebuffer(width, height);
}

GloveWindow::~GloveWindow() {
	glfwDestroyWindow(glfwWindow);
}

void GloveWindow::MakeCurrent() {
	glfwMakeContextCurrent(glfwWindow);
}

bool GloveWindow::CloseRequested() {
	return glfwWindowShouldClose(glfwWindow);
}

void GloveWindow::SetFramebuffer(int width, int height) {
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

void GloveWindow::SwapBuffers() {
	glfwSwapBuffers(glfwWindow);
}

void GloveWindow::OnKeyEvent(int key, int scancode, int action, int mods) {
	KeyAction keyAction = (action == GLFW_PRESS) ? KA_PRESS : ((action == GLFW_RELEASE) ? KA_RELEASE : KA_REPEAT);
	KeyEvent keyEvent((KeyCode)key, keyAction, mods & GLFW_MOD_ALT, mods & GLFW_MOD_CONTROL, mods & GLFW_MOD_SHIFT, mods & GLFW_MOD_SUPER);
	gloveCore->GetEventBusRef()->Publish(keyEvent);
}

void GloveWindow::GlfwFramebufferSizeChanged(GLFWwindow* window, int width, int height) {
	GloveWindow* gloveWindow = reinterpret_cast<GloveWindow*>(glfwGetWindowUserPointer(window));
	gloveWindow->SetFramebuffer(width, height);
}

void GloveWindow::GlfwKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	GloveWindow* gloveWindow = reinterpret_cast<GloveWindow*>(glfwGetWindowUserPointer(window));
	gloveWindow->OnKeyEvent(key, scancode, action, mods);
}

void GloveWindow::GlfwCloseEvent(GLFWwindow *window) {
    //TODO: Schedule window close
}

std::string GloveWindow::GetContextVersion() {
    return (boost::format("OpenGL %1%.%2%.%3%")
            % glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_VERSION_MAJOR)
            % glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_VERSION_MINOR)
            % glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_REVISION)).str();
}
} // namespace glove