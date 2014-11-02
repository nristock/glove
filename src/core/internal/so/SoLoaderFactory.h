#pragma once
#if defined(__unix__) || defined(__unix)

#include <core/ISharedLibraryLoaderFactory.h>

namespace glove {

class SoLoaderFactory : public ISharedLibraryLoaderFactory {

public:
    virtual ~SoLoaderFactory() {}

    virtual ISharedLibraryLoaderPtr CreateLibraryLoader(const std::string& libraryFilePath);
};

} /* namespace glove */
#endif