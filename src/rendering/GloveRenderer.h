/*
 * GloveRenderer.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef GLOVERENDERER_H_
#define GLOVERENDERER_H_

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

struct GLFWwindow;

namespace glove {
class GloveWindow;

class GloveRenderer : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GloveRenderer")
public:
	GloveRenderer();
	virtual ~GloveRenderer();

	GloveWindowPointer Init(int windowWidth, int windowHeight, int glMajor, int glMinor, int argc, char** argv);
	void Exit();

	void RenderScene(GloveWindowPointer window /* Scenegraph */);

private:
	void SetViewport(int width, int height);

	static void GlfwErrorSink(int error, const char* description);	
};

} /* namespace glove */

#endif /* GLOVERENDERER_H_ */
