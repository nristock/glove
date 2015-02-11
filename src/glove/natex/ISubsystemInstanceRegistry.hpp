#pragma once

#include <list>

#include "glove/natex/Natex.hpp"

namespace glove {

class GLOVE_API_EXPORT ISubsystemInstanceRegistry {
  public:
    virtual ~ISubsystemInstanceRegistry() {}
    virtual void InstantiateDefinitionRegistry(const ISubsystemDefinitionRegistryPtr& definitionRegistry) = 0;

    virtual SubsystemInstanceList GetSubsystemsOfType(const SubsystemType& subsystemType) = 0;
    virtual ISubsystemPtr GetUniqueSubsystemOfType(const SubsystemType& subsystemType) = 0;
};

} /* namespace glove */