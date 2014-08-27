/*
 * GloveCore.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "GloveCore.h"

#include "GloveException.h"
#include "rendering/GloveRenderer.h"

namespace glove {

GloveCore::GloveCore() {
	OLOG(info) << "GloveCore created";

	renderer = GloveRendererPtr(new GloveRenderer());
}

GloveCore::~GloveCore() {
}

void GloveCore::InitializeRenderingContext(int argc, char** argv, int windowWidth, int windowHeight) {
	try {
		renderer->Init(windowWidth, windowHeight, 3, 1, argc, argv);
	} catch (GloveException& e) {
		OLOG(error) << "Exception while initializing rendering subsystem:" << std::endl << e.what();
	}

}

} /* namespace glove */
