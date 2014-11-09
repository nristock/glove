#if defined(ON_UNIX)

#include "SoLoader.h"

#include <dlfcn.h>

#include <boost/format.hpp>

#include <core/GloveException.h>

namespace glove {
SoLoader::SoLoader(const std::string& soFilePath) {
    libraryHandle = dlopen(soFilePath.c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (!libraryHandle) {
        throw GLOVE_EXCEPTION((boost::format("Failed to load SO library %1%: %2%") % soFilePath % dlerror()).str());
    }
}

SoLoader::~SoLoader() {
    if (libraryHandle) {
        if (dlclose(libraryHandle)) {
            LOG(logger, error, (boost::format("Failed to unload SO library %1%: %2%") % libraryHandle % dlerror()).str());
        }
    }
}

void* SoLoader::LoadSymbol(const std::string& symbolName) {
    void* symbolAddress = dlsym(libraryHandle, symbolName.c_str());

    if (!symbolAddress) {
        throw GLOVE_EXCEPTION((boost::format("Failed to load SO symbol %1%: %2%") % symbolName % dlerror()).str());
    }

    return symbolAddress;
}
}

#endif
