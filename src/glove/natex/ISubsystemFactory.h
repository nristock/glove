#pragma once

#include "glove/natex/Natex.h"

namespace glove {

class ISubsystemFactory {
  public:
    virtual ~ISubsystemFactory(){};

    virtual ISubsystemPtr CreateSubsystem(const GloveCorePtr& engineCore) = 0;
};

} /* namespace glove */