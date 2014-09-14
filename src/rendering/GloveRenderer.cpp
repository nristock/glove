/*
 * GloveRenderer.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */
#include "GloveRenderer.h"

#include <sstream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/GloveException.h"
#include "graph/Scenegraph.h"
#include "rendering/Camera.h"
#include "rendering/IRenderable.h"
#include "rendering/FrameData.h"
#include "log/Log.h"
#include "GloveWindow.h"

#ifdef WIN32
#define snprintf _snprintf
#endif

namespace glove {

GloveRenderer::GloveRenderer() {	
}

GloveRenderer::~GloveRenderer() {
	// TODO Auto-generated destructor stub
}

void GloveRenderer::Init(int windowWidth, int windowHeight, int glMajor, int glMinor, int argc, char** argv) {
	glfwSetErrorCallback(&GloveRenderer::GlfwErrorSink);
	
	if (!glfwInit()) {
		throw GloveException("GLFW Initialization failed.");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	associatedWindow = GloveWindowPtr(new GloveWindow());
	associatedWindow->Init(windowWidth, windowHeight);
	associatedWindow->MakeCurrent();

	glewExperimental = GL_TRUE;
	GLenum glewInitRes = glewInit();
	if (glewInitRes != GLEW_OK) {
		throw GloveException(std::string((char*)glewGetErrorString(glewInitRes)));
	}

	OLOG(info, "Glove renderer initialized");
	OLOG(info, "OpenGL Version: " << glGetString(GL_VERSION));
}

void GloveRenderer::Exit() {
	glfwTerminate();
}

void GloveRenderer::GlfwErrorSink(int error, const char* description) {
	LOG(logging::globalLogger, error, "GLFW Error (" << error << "): " << description);
}

void GloveRenderer::RenderScene(ScenegraphPointer scenegraph, FrameData& frameData) {
	frameData.viewProjectionMatrix = associatedWindow->GetProjMatrix() * scenegraph->GetMainCamera()->GetViewMatrix();

	scenegraph->IterateGameObjects([&](GameObjectPtr gameObject){
		gameObject->IterateRenderableComponents([&](IRenderablePtr renderable) {
			renderable->Render(frameData);
		});			
	});

	associatedWindow->SwapBuffers();
}

} /* namespace glove */
