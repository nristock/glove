#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/natex/ISystemExtension.h"

namespace glove {

/// @brief Loads a system extension by file-path.
class ISystemExtensionLoader {
  public:
    virtual ~ISystemExtensionLoader() {}

    /// @brief Loads a system extension.
    ///
    /// @param extensionName [in] The extension's file path.
    virtual ISystemExtensionPtr LoadSystemExtension(const std::string& extensionName) = 0;

    /// @brief Unloads a system extension.
    ///
    /// @param systemExtension [in/out] The extension to unload. The smart pointer will be invalidated by this!
    virtual void UnloadSystemExtension(ISystemExtensionPtr& systemExtension) = 0;
};

} /* namespace glove */