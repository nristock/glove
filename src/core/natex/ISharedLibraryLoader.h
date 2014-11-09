#pragma once

#include <string>

namespace glove {

/// @brief Interface for shared library loaders.
///
/// A shared library loader is an object bound to a specific shared library file (.so, .dll) and will be used as an
/// interface to load symbols (primarily the LoadExtension and UnloadExtension functions) from the library.
class ISharedLibraryLoader {
public:
    virtual ~ISharedLibraryLoader() {};

    /// @brief Loads a named symbol from the library.
    ///
    /// @param symbolName [in] The name of the symbol to load.
    /// @return Returns a pointer to the loaded symbol or throws a GloveException.
    virtual void* LoadSymbol(const std::string& symbolName) = 0;
};

} /* namespace glove */