#pragma once
#if defined(ON_UNIX)

#include "glove/natex/ISharedLibraryLoaderFactory.hpp"

namespace glove {

class SoLoaderFactory : public ISharedLibraryLoaderFactory {
  public:
    virtual ISharedLibraryLoaderPtr CreateLibraryLoader(const std::string& libraryFilePath);
};

} /* namespace glove */
#endif