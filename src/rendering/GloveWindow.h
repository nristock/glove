#pragma once

#include <glm/glm.hpp>

#include "core/GloveObject.h"

struct GLFWwindow;

namespace glove{

class GloveWindow : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GloveWindow")
public:
	GloveWindow();
    GloveWindow(GloveWindowPtr parent);
	virtual ~GloveWindow();

	virtual void Init(int width, int height);

	virtual void MakeCurrent();
	virtual void SetFramebuffer(int newWidth, int newHeight);

	virtual void SwapBuffers();
	virtual bool CloseRequested();

    virtual std::string GetContextVersion();

	glm::mat4 GetProjMatrix() const { return projectionMat; }

private:
	GLFWwindow* glfwWindow;
    GLFWwindow* parent;

	int viewportWidth, viewportHeight;
	float aspectRatio;
	float orthoSize;
	glm::mat4 projectionMat;

	void OnKeyEvent(int key, int scancode, int action, int mods);

    GLFWwindow* GetGlfwWindow() const { return glfwWindow; }

	static void GlfwFramebufferSizeChanged(GLFWwindow* window, int width, int height);
	static void GlfwKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void GlfwCloseEvent(GLFWwindow* window);
};

} // namespace glove