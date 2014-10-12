#pragma once

#include "core/GloveFwd.h"
#include "log/Log.h"
#include "memory/GloveMemory.h"

#define OLOG(lvl_, lgs_) LOG(this->logger, lvl_, lgs_)

namespace glove {

class GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GloveObject")

public:
	GloveObject();
	GloveObject(bool queryGloveCore);
	virtual ~GloveObject();

protected:
	logging::GloveLogger logger;

	GloveCorePtr gloveCore;
};

} /* namespace glove */
