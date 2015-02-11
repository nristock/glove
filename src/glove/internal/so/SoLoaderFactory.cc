#if defined(ON_UNIX)

#include "glove/internal/so/SoLoaderFactory.hpp"
#include "glove/internal/so/SoLoader.hpp"

namespace glove {
ISharedLibraryLoaderPtr glove::SoLoaderFactory::CreateLibraryLoader(const std::string& libraryFilePath) {
    return std::make_shared<SoLoader>(libraryFilePath);
}
}

#endif
