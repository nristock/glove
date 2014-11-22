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
}