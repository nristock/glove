/*
 * GloveCore.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef GLOVECORE_H_
#define GLOVECORE_H_

#include "GloveFwd.h"

#include "rendering/GloveRenderer.h"
#include "GloveObject.h"

namespace glove {

class GloveCore : public GloveObject {
public:
	GloveCore();
	virtual ~GloveCore();

	void InitializeRenderingContext(int argc, char** argv, int windowWidth, int windowHeight);

private:
	GloveRendererPtr renderer;
};

} /* namespace glove */

#endif /* GLOVECORE_H_ */
