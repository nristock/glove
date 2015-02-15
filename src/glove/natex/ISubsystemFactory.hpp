#pragma once

#include "glove/natex/Natex.hpp"

namespace glove {

class GLOVE_API_EXPORT ISubsystemFactory {
  public:
    virtual ~ISubsystemFactory(){};

    virtual ISubsystemPtr CreateSubsystem(const ISubsystemInstanceRegistryPtr& subsystemInstanceRegistry, const EventBusPtr& eventBus) = 0;
};

} /* namespace glove */