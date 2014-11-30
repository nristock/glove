#include "GloveSubsystemInstanceRegistry.h"

#include <core/GloveException.h>
#include <core/events/EventBus.h>
#include <core/events/type/PreSubsystemCreateEvent.h>
#include <core/events/type/SubsystemCreatedEvent.h>

#include "ISubsystemDefinition.h"
#include "ISubsystemDefinitionRegistry.h"
#include "ISubsystemFactory.h"
#include "ISubsystem.h"

namespace glove {

GloveSubsystemInstanceRegistry::GloveSubsystemInstanceRegistry(const EventBusPtr& eventBus,
                                                               const GloveCorePtr& engineCore)
    : eventBus(eventBus), engineCore(engineCore) {}

void GloveSubsystemInstanceRegistry::InstantiateDefinitionRegistry(
    const ISubsystemDefinitionRegistryPtr& definitionRegistry) {
    for (const ISubsystemDefinitionPtr& subsystemDefinition :
         definitionRegistry->GetTopologicallySortedSubsystemDefinitions()) {
        try {
            EmitPreCreateEvent();

            ISubsystemFactoryPtr subsystemFactory = subsystemDefinition->GetSystemFactory();
            ISubsystemPtr subsystemInstance = subsystemFactory->CreateSubsystem(engineCore);

            subsystemInstances.insert(
                std::pair<SubsystemType, ISubsystemPtr>(subsystemDefinition->GetSystemType(), subsystemInstance));

            EmitPostCreateEvent();
        }
        catch (GloveException& ex) {
            LOG(logger, error, ex.what());
        }
    }
}

void GloveSubsystemInstanceRegistry::EmitPreCreateEvent() { eventBus->Publish(PreSubsystemCreateEvent()); }

void GloveSubsystemInstanceRegistry::EmitPostCreateEvent() { eventBus->Publish(SubsystemCreatedEvent()); }

SubsystemInstanceList GloveSubsystemInstanceRegistry::GetSubsystemsOfType(const SubsystemType& subsystemType) {
    std::list<ISubsystemPtr> instances;

    std::pair<SubsystemInstanceMap::const_iterator, SubsystemInstanceMap::const_iterator> instanceRange =
        subsystemInstances.equal_range(subsystemType);

    for (auto& iter = instanceRange.first; iter != instanceRange.second; ++iter) {
        instances.push_back(iter->second);
    }

    return instances;
}

ISubsystemPtr GloveSubsystemInstanceRegistry::GetUniqueSubsystemOfType(const SubsystemType& subsystemType) {
    SubsystemInstanceList subsystemInstances = GetSubsystemsOfType(subsystemType);

    if(subsystemInstances.size() > 1) {
        throw GLOVE_EXCEPTION("Found more than one subsystem instancen of type") //todo
    }

    if(subsystemInstances.empty()) {
        throw GLOVE_EXCEPTION("Couldn't find any subsystem instance of type") //todo
    }

    return *subsystemInstances.begin();
}
}