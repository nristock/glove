#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/natex/Module.hpp"

namespace glove {

/// @brief Loads a system extension by file-path.
class GLOVE_API_EXPORT ModuleLoader {
  public:
    virtual ~ModuleLoader() {}

    /// @brief Loads a system extension.
    ///
    /// @param extensionName [in] The extension's file path.
    virtual std::unique_ptr<glove::Module> LoadModule(const std::string &extensionName) = 0;
};

} /* namespace glove */