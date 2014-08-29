/*
 * GloveRenderer.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef GLOVERENDERER_H_
#define GLOVERENDERER_H_

#include <memory>

#include <glm/glm.hpp>

#include "core/GloveObject.h"

namespace glove {

class GloveRenderer : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GloveRenderer")
public:
	GloveRenderer();
	virtual ~GloveRenderer();

	void Init(int windowWidth, int windowHeight, int glMajor, int glMinor, int argc, char** argv, float orthoSize = 10);

private:
	int viewportWidth, viewportHeight;
	float aspectRatio;
	float orthoSize;
	glm::mat4 viewMat;
	glm::mat4 projectionMat;

	static GloveRenderer* instance;

	void SetViewport(int width, int height);

	static void GlutErrorSink(const char* fmt, va_list vp);
	static void GlutWarningSink(const char* fmt, va_list vp);
	static void GlutWindowResized(int width, int height);
};

} /* namespace glove */

#endif /* GLOVERENDERER_H_ */
