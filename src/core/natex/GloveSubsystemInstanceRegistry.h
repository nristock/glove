#pragma once

#include <map>

#include <core/GloveFwd.h>
#include <core/log/Log.h>

#include "Natex.h"
#include "ISubsystemInstanceRegistry.h"

namespace glove {

class GloveSubsystemInstanceRegistry : public ISubsystemInstanceRegistry {
public:
    GloveSubsystemInstanceRegistry(const EventBusPtr& eventBus, const GloveCorePtr& engineCore);

    virtual void InstantiateDefinitionRegistry(ISubsystemDefinitionRegistryPtr const& definitionRegistry) override;

private:
    logging::GloveLogger logger;
    EventBusPtr eventBus;
    GloveCorePtr engineCore;
    std::multimap<SubsystemType, ISubsystemPtr> subsystemInstances;

    void EmitPreCreateEvent();

    void EmitPostCreateEvent();
};

} /* namespace glove */