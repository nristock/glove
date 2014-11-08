#pragma once

#include <core/GloveFwd.h>
#include "ISystemExtension.h"

namespace glove {

class ISystemExtensionLoader {
public:
    virtual ~ISystemExtensionLoader() {}

    /// @brief Loads a system extension.
    ///
    /// @param extensionName [in] The extension's name. This can either be an actual file path or just a simple name
    ///                           depending on the extension finder used to discover the extension.
    virtual ISystemExtensionPtr LoadSystemExtension(const std::string& extensionName) = 0;

    /// @brief Unloads a system extension.
    ///
    /// @param systemExtension [in] The extension to unload.
    virtual void UnloadSystemExtension(const ISystemExtensionPtr& systemExtension) = 0;
};

} /* namespace glove */