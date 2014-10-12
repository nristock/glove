#pragma once

#include <glm/glm.hpp>

#include "core/GloveObject.h"
#include "core/IWindow.h"

struct GLFWwindow;

namespace glove{

class GLWindow : public GloveObject, public IWindow {
	GLOVE_MEM_ALLOC_FUNCS("GLWindow")
public:
	GLWindow(int width, int height);
    GLWindow(int width, int height, WindowPtr parent);
	virtual ~GLWindow();

	virtual void MakeCurrent();
	virtual void SetFramebuffer(int newWidth, int newHeight);

	virtual void SwapBuffers();
	virtual bool CloseRequested() const;

    virtual std::string GetContextVersion() const;

	virtual glm::mat4 GetProjMatrix() const { return projectionMat; }

private:
	GLFWwindow* glfwWindow;
    GLFWwindow* parent;

	int viewportWidth, viewportHeight;
	float aspectRatio;
	float orthoSize;
	glm::mat4 projectionMat;

	void OnKeyEvent(int key, int scancode, int action, int mods);
	void OnMouseMove(double x, double y);
	void OnMouseButton(int button, int action, int mods);

    GLFWwindow* GetGlfwWindow() const { return glfwWindow; }

	static void GlfwFramebufferSizeChanged(GLFWwindow* window, int width, int height);
	static void GlfwKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void GlfwCloseEvent(GLFWwindow* window);
	static void GlfwCursorPositionChanged(GLFWwindow* window, double x, double y);
	static void GlfwMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
};

} // namespace glove