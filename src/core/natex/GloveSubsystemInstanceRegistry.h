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

    virtual void InstantiateDefinitionRegistry(const ISubsystemDefinitionRegistryPtr& definitionRegistry);
    virtual SubsystemInstanceList GetSubsystemsOfType(const SubsystemType& subsystemType);
    virtual ISubsystemPtr GetUniqueSubsystemOfType(const SubsystemType& subsystemType);

private:
    typedef std::multimap<SubsystemType, ISubsystemPtr> SubsystemInstanceMap;

    logging::GloveLogger logger;
    EventBusPtr eventBus;
    GloveCorePtr engineCore;
    SubsystemInstanceMap subsystemInstances;

    void EmitPreCreateEvent();
    void EmitPostCreateEvent();
};

} /* namespace glove */