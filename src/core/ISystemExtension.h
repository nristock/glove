#pragma once

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
    /// @param engineCore [in] A shared_ptr to the engine core currently being initialized.
    virtual void RegisterSubsystems(const GloveCorePtr& engineCore) = 0;
};

} /* namespace glove */