#pragma once
#if defined(ON_UNIX)

#include <core/natex/ISharedLibraryLoaderFactory.h>

namespace glove {

class SoLoaderFactory : public ISharedLibraryLoaderFactory {

public:
    virtual ~SoLoaderFactory() {}

    virtual ISharedLibraryLoaderPtr CreateLibraryLoader(const std::string& libraryFilePath);
};

} /* namespace glove */
#endif