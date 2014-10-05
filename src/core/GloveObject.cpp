/*
 * GloveObject.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "GloveObject.h"

#include "core/GloveCore.h"

namespace glove {

GloveObject::GloveObject() : GloveObject(true) {
}

GloveObject::GloveObject(bool queryGloveCore) {
	if (queryGloveCore) {
		gloveCore = GloveCore::Instance();
	}
}

GloveObject::~GloveObject() {
}

} /* namespace glove */
