#include "GloveWindow.h"

#include "core/GloveCore.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


#include "event/EventBus.h"
#include "event/type/KeyEvent.h"

namespace glove {

GloveWindow::GloveWindow() : orthoSize(10), viewportWidth(0), viewportHeight(0), aspectRatio(0) {
}

void GloveWindow::Init(int width, int height) {
	glfwWindow = glfwCreateWindow(width, height, "glove", NULL, NULL);
	glfwSetWindowUserPointer(glfwWindow, this);
	glfwSetFramebufferSizeCallback(glfwWindow, &GloveWindow::GlfwFramebufferSizeChanged);
	glfwSetKeyCallback(glfwWindow, &GloveWindow::GlfwKeyEvent);

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

	glViewport(0, 0, width, height);
	
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

} // namespace glove