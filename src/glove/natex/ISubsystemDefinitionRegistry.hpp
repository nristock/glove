#pragma once

#include "glove/natex/Natex.hpp"

namespace glove {

/// @brief Interface for a subsystem registry.
///
/// A subsystem registry is responsible for maintaining a list of all available subsystem types and implementations
/// provided. It furthermore is responsible for maintaining the mapping between system types and selected
/// implementations. The registry is also used to create and initialize subsystem implementations.
class ISubsystemDefinitionRegistry {
  public:
    virtual ~ISubsystemDefinitionRegistry() {}

    /// @brief Registers a subsystem definition thus providing a subsystem implementation for a specific system type.
    ///
    /// It is up to the implementation whether an unknown subsystem type raises an exception or if the subsystem type
    /// is automatically registered.
    virtual void RegisterSubsystemDefinition(const ISubsystemDefinitionPtr& subsystemDefinition) = 0;

    /// @brief Registers a subsystem type.
    virtual void RegisterSubsystemType(const SubsystemType& subsystemType) = 0;

    /// @brief Returns a consistent and topologically sorted list of all registered subsystem definitions.
    ///
    /// The list is consistent if there is an implementing subsystem for each subsystem type required by at least one
    /// subsystem as a dependency.
    virtual SubsystemDefinitionList GetTopologicallySortedSubsystemDefinitions() = 0;
};

} /* namespace glove */