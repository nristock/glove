#pragma once

#include <map>

#include "glove/GloveFwd.hpp"
#include "glove/log/Log.hpp"
#include "glove/natex/Natex.hpp"
#include "glove/natex/ISubsystemInstanceRegistry.hpp"

namespace glove {

class GLOVE_API_EXPORT GloveSubsystemInstanceRegistry : public ISubsystemInstanceRegistry, public std::enable_shared_from_this<ISubsystemInstanceRegistry> {
  public:
    GloveSubsystemInstanceRegistry(const EventBusPtr& eventBus);

    virtual void InstantiateDefinitionRegistry(const ISubsystemDefinitionRegistryPtr& definitionRegistry);
    virtual SubsystemInstanceList GetSubsystemsOfType(const SubsystemType& subsystemType);
    virtual ISubsystemPtr GetUniqueSubsystemOfType(const SubsystemType& subsystemType);

  private:
    typedef std::multimap<SubsystemType, ISubsystemPtr> SubsystemInstanceMap;

    logging::GloveLogger logger;
    EventBusPtr eventBus;
    SubsystemInstanceMap subsystemInstances;

    void EmitPreCreateEvent();
    void EmitPostCreateEvent();
};

} /* namespace glove */