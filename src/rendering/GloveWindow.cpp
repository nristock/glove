#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "GloveWindow.h"

namespace glove {

GloveWindow::GloveWindow() : orthoSize(10), viewportWidth(0), viewportHeight(0), aspectRatio(0) {
}

void GloveWindow::Init(int width, int height) {
	glfwWindow = glfwCreateWindow(width, height, "glove", NULL, NULL);
	glfwSetWindowUserPointer(glfwWindow, this);
	glfwSetFramebufferSizeCallback(glfwWindow, &GloveWindow::GlfwFramebufferSizeChanged);

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

	viewMat = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
}

void GloveWindow::SwapBuffers() {
	glfwSwapBuffers(glfwWindow);
}

void GloveWindow::GlfwFramebufferSizeChanged(GLFWwindow* window, int width, int height) {
	GloveWindow* gloveWindow = reinterpret_cast<GloveWindow*>(glfwGetWindowUserPointer(window));
	gloveWindow->SetFramebuffer(width, height);
}

} // namespace glove