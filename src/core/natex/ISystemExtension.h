#pragma once

#include <boost/uuid/uuid.hpp>

#include "Natex.h"

#include <core/GloveFwd.h>

namespace glove {

/// @brief Interface for system extension.
///
/// System extension are engine extension which fundamentally modify the engine's functionality.
/// This usually includes scripting systems, renderer implementations and other pluggable systems.
class ISystemExtension {
public:
    virtual ~ISystemExtension() {}

    /// @brief Registers all subsystems the extension module provides.
    ///
    /// @param engineCore [in] A shared_ptr to the subsystem registry.
    virtual void RegisterSubsystems(const ISubsystemDefinitionRegistryPtr& subsystemRegistry) = 0;

    virtual const ExtensionUuid GetExtensionUuid() const = 0;

    virtual const std::string& GetExtensionName() const = 0;
};

} /* namespace glove */