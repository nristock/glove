#include "GloveSubsystemDefinitionRegistry.h"

#include <boost/format.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <core/GloveException.h>

#include "internal/ExtensionDependencyGraph.h"
#include "ISubsystemDefinition.h"

namespace glove {
GloveSubsystemDefinitionRegistry::GloveSubsystemDefinitionRegistry() {
}

GloveSubsystemDefinitionRegistry::~GloveSubsystemDefinitionRegistry() {
}

void GloveSubsystemDefinitionRegistry::RegisterSubsystemDefinition(const ISubsystemDefinitionPtr& subsystemDefinition) {
    subsystemDefinitions.insert(
        std::pair<SubsystemType, ISubsystemDefinitionPtr>(subsystemDefinition->GetSystemType(), subsystemDefinition));
}

void GloveSubsystemDefinitionRegistry::RegisterSubsystemType(const SubsystemType& subsystemType) {
    // NOP
}

SubsystemDefinitionList GloveSubsystemDefinitionRegistry::GetTopologicallySortedSubsystemDefinitions() {
    if (topologicallySortedDefinitions.empty()) {
        PerformTopologicalSort();
        CheckConsistency();
    }

    return topologicallySortedDefinitions;
}

void GloveSubsystemDefinitionRegistry::PerformTopologicalSort() {
    SubsystemDefinitionList unsortedSubsystems;

    for (auto& multiMapPair : subsystemDefinitions) {
        unsortedSubsystems.push_back(multiMapPair.second);
    }

    ExtensionDependencyGraph dependencyGraph(unsortedSubsystems);
    topologicallySortedDefinitions = dependencyGraph.GetSortedList();
}

void GloveSubsystemDefinitionRegistry::CheckConsistency() {
    for (const auto& multiMapPair : subsystemDefinitions) {
        for (const SubsystemType& subsystemType : multiMapPair.second->GetSystemDependencies()) {
            if (subsystemDefinitions.count(subsystemType) == 0) {
                throw GLOVE_EXCEPTION((boost::format("Inconsistent subsystem registry. Requirement for subsystem type "
                                                     "%1% has not been satisfied.") %
                                       subsystemType).str());
            }
        }
    }
}
}
