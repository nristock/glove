#pragma once

#include "glove/GloveApi.hpp"
#include "glove/natex/Natex.hpp"

namespace glove {

/// @brief Interface for shared library loder factories.
class GLOVE_API_EXPORT ISharedLibraryLoaderFactory {
  public:
    virtual ~ISharedLibraryLoaderFactory(){};

    /// @brief Creates a shared library loader object designated to libraryFilePath.
    ///
    /// @param libraryFilePath [in] The path to the library file to load.
    /// @return Returns a shared_ptr to the library loader instance.
    virtual ISharedLibraryLoaderPtr CreateLibraryLoader(const std::string& libraryFilePath) = 0;
};

} /* namespace glove */