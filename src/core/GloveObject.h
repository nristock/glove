#pragma once

#include "core/GloveFwd.h"
#include "log/Log.h"
#include "pitamem/MemoryProfile.h"

#define OLOG(lvl_, lgs_) LOG(this->logger, lvl_, lgs_)

namespace glove {

/** Base class for pretty much all engine objects. Provides easy access to the engine's logging interface. */
class GloveObject {
Profilable()
public:
    GloveObject();

    GloveObject(bool queryGloveCore);

    virtual ~GloveObject();

protected:
    /** Local logger */
    logging::GloveLogger logger;

    GloveCorePtr gloveCore;
};

} /* namespace glove */
