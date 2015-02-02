#pragma once

#include "glove/natex/Natex.h"

namespace glove {

/// @brief Interface for shared library loder factories.
class ISharedLibraryLoaderFactory {
  public:
    virtual ~ISharedLibraryLoaderFactory(){};

    /// @brief Creates a shared library loader object designated to libraryFilePath.
    ///
    /// @param libraryFilePath [in] The path to the library file to load.
    /// @return Returns a shared_ptr to the library loader instance.
    virtual ISharedLibraryLoaderPtr CreateLibraryLoader(const std::string& libraryFilePath) = 0;
};

} /* namespace glove */