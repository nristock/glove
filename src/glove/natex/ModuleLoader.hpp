#pragma once

#include "glove/BlueDwarfFwd.hpp"
#include "glove/natex/Module.hpp"

namespace BlueDwarf {

/// @brief Loads a system extension by file-path.
class BD_API_EXPORT ModuleLoader {
  public:
    virtual ~ModuleLoader() {}

    /// @brief Loads a system extension.
    ///
    /// @param extensionName [in] The extension's file path.
    virtual std::unique_ptr<BlueDwarf::Module> LoadModule(const std::string& extensionName) = 0;
};

} /* namespace BlueDwarf */