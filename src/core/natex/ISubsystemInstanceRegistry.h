#pragma once

#include <list>

#include "Natex.h"

namespace glove {

class ISubsystemInstanceRegistry {
public:
    virtual ~ISubsystemInstanceRegistry() {}
    virtual void InstantiateDefinitionRegistry(const ISubsystemDefinitionRegistryPtr& definitionRegistry) = 0;

    virtual SubsystemInstanceList GetSubsystemsOfType(const SubsystemType& subsystemType) = 0;
    virtual ISubsystemPtr GetUniqueSubsystemOfType(const SubsystemType& subsystemType) = 0;
};

} /* namespace glove */