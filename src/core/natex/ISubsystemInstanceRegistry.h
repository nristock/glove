#pragma once

#include "Natex.h"

namespace glove {

class ISubsystemInstanceRegistry {
public:
    virtual ~ISubsystemInstanceRegistry() {}

    virtual void InstantiateDefinitionRegistry(const ISubsystemDefinitionRegistryPtr& definitionRegistry) = 0;
};

} /* namespace glove */