/*
 * GloveCore.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "GloveException.h"
#include "GloveCore.h"

namespace glove {
namespace core {

using namespace gl;

GloveCore::GloveCore() {
	OLOG(info) << "GloveCore created";

	renderer = rendering::GloveRendererPtr(new rendering::GloveRenderer());
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

} /* namespace core */
} /* namespace glove */
