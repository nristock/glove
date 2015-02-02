#pragma once

#include <list>
#include <map>

#include "glove/natex/ISubsystemDefinitionRegistry.h"
#include "glove/GloveFwd.hpp"
#include "glove/log/Log.h"

namespace glove {

/// @brief Default implementation for subsystem registry
class GloveSubsystemDefinitionRegistry : public ISubsystemDefinitionRegistry {
  public:
    GloveSubsystemDefinitionRegistry();
    virtual ~GloveSubsystemDefinitionRegistry();

    virtual void RegisterSubsystemDefinition(const ISubsystemDefinitionPtr& subsystemDefinition);

    /// @brief NOP in this implementation.
    virtual void RegisterSubsystemType(const SubsystemType& subsystemType);

    virtual SubsystemDefinitionList GetTopologicallySortedSubsystemDefinitions();

  private:
    logging::GloveLogger logger;

    std::multimap<SubsystemType, ISubsystemDefinitionPtr> subsystemDefinitions;
    SubsystemDefinitionList topologicallySortedDefinitions;
    EventBusPtr eventBus;

    void PerformTopologicalSort();
    void CheckConsistency();
};

} /* namespace glove */