#ifndef GLOVEWINDOW_H_
#define GLOVEWINDOW_H_

#include <glm/glm.hpp>

#include "core/GloveObject.h"

struct GLFWwindow;

namespace glove{

class GloveWindow : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GloveWindow")
public:
	GloveWindow();
	virtual ~GloveWindow();

	virtual void Init(int width, int height);

	virtual void MakeCurrent();
	virtual void SetFramebuffer(int newWidth, int newHeight);

	virtual void SwapBuffers();
	virtual bool CloseRequested();

	glm::mat4 GetProjMatrix() const { return projectionMat; }

private:
	GLFWwindow* glfwWindow;

	int viewportWidth, viewportHeight;
	float aspectRatio;
	float orthoSize;
	glm::mat4 projectionMat;

	static void GlfwFramebufferSizeChanged(GLFWwindow* window, int width, int height);
};

} // namespace glove

#endif