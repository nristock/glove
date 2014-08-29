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
#include <GL/gl.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/GloveException.h"
#include "log/log.h"

#ifdef WIN32
#define snprintf _snprintf
#endif

namespace glove {

GloveRenderer* GloveRenderer::instance = NULL;

GloveRenderer::GloveRenderer() : viewportWidth(0), viewportHeight(0), aspectRatio(0), orthoSize(10) {
	// TODO Auto-generated constructor stub

}

GloveRenderer::~GloveRenderer() {
	// TODO Auto-generated destructor stub
}

void GloveRenderer::Init(int windowWidth, int windowHeight, int glMajor, int glMinor, int argc, char** argv, float orthoSize) {
	if(instance) {
		throw new GloveException("GloveRenderer::Init has already been called.");
	}

	instance = this;
	this->orthoSize = orthoSize;

	glutInitErrorFunc(&GloveRenderer::GlutErrorSink);
	glutInitWarningFunc(&GloveRenderer::GlutWarningSink);

	glutInit(&argc, argv);
	glutInitContextVersion(glMajor, glMinor);

	glutInitContextFlags (GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile (GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(windowWidth, windowHeight);

	glutInitWindowPosition(0, 0);

	glutReshapeFunc(&GloveRenderer::GlutWindowResized);
	glutCreateWindow("Glove");

	glewExperimental = GL_TRUE;
	GLenum glewInitRes = glewInit();
	if (glewInitRes != GLEW_OK) {
		throw GloveException(std::string((char*)glewGetErrorString(glewInitRes)));
	}

	glViewport(0, 0, windowWidth, windowHeight);
	viewportWidth = windowWidth;
	viewportHeight = windowHeight;

	OLOG(info, "Glove renderer initialized");
	OLOG(info, "OpenGL Version: " << glGetString(GL_VERSION));
}

void GloveRenderer::GlutErrorSink(const char *fmt, va_list vp) {
	int bufferSize = 100;
	char* buffer = new char[bufferSize];
	
	int totalSize = snprintf(buffer, bufferSize, fmt, vp);
	if(totalSize > 0 && totalSize > bufferSize) {
		delete[] buffer;
		buffer = new char[totalSize];

		snprintf(buffer, totalSize, fmt, vp);
	}

	LOG(logging::globalLogger, error, "GLUT Error: " << buffer);
	delete[] buffer;
}

void GloveRenderer::GlutWarningSink(const char *fmt, va_list vp) {
	int bufferSize = 100;
	char* buffer = new char[bufferSize];

	int totalSize = snprintf(buffer, bufferSize, fmt, vp);
	if(totalSize > 0 && totalSize > bufferSize) {
		delete[] buffer;
		buffer = new char[totalSize];

		snprintf(buffer, totalSize, fmt, vp);
	}

	//LOG(logging::globalLogger, warning) << "GLUT Error: " << buffer;
	delete[] buffer;
}

void GloveRenderer::GlutWindowResized(int width, int height) {
	if(instance) instance->SetViewport(width, height);
	else LOG(logging::globalLogger, error, "GlutWindowReshape callback called but no renderer instance was set.");
}

void GloveRenderer::SetViewport(int width, int height) {
	glViewport(0, 0, width, height);

	viewportWidth = width;
	viewportHeight = height;

	aspectRatio = width / height;
	projectionMat = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio);

	viewMat = glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
}

} /* namespace glove */
