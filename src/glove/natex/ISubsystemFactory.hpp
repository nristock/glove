#pragma once

#include "glove/natex/Natex.hpp"

namespace glove {

class ISubsystemFactory {
  public:
    virtual ~ISubsystemFactory(){};

    virtual ISubsystemPtr CreateSubsystem(const GloveCorePtr& engineCore) = 0;
};

} /* namespace glove */