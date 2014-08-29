/*
 * GloveObject.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef GLOVEOBJECT_H_
#define GLOVEOBJECT_H_

#include "log/Log.h"
#include "memory/GloveMemory.h"

#define OLOG(lvl_, lgs_) LOG(this->logger, lvl_, lgs_)

namespace glove {

class GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GloveObject")

public:
	GloveObject();
	virtual ~GloveObject();

protected:
	logging::GloveLogger logger;
};

} /* namespace glove */

#endif /* GLOVEOBJECT_H_ */
