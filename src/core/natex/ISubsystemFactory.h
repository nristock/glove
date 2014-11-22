#pragma once

#include "Natex.h"

namespace glove {

class ISubsystemFactory {
public:
    virtual ~ISubsystemFactory() {};

    virtual ISubsystemPtr CreateSubsystem(const GloveCorePtr& engineCore) = 0;
};

} /* namespace glove */