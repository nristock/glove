#if defined(ON_UNIX)

#include "SoLoader.h"

#include <dlfcn.h>

#include <boost/format.hpp>

#include <core/GloveException.h>

namespace glove {
SoLoader::SoLoader(const std::string& soFilePath) : libraryFile(soFilePath) { LoadLibrary(); }

SoLoader::~SoLoader() {
    if (libraryHandle) {
        UnloadLibrary();
    }
}

void* SoLoader::LoadSymbol(const std::string& symbolName) {
    void* symbolAddress = dlsym(libraryHandle, symbolName.c_str());

    if (!symbolAddress) {
        throw GLOVE_EXCEPTION((boost::format("Failed to load SO symbol %1%: %2%") % symbolName % dlerror()).str());
    }

    return symbolAddress;
}

void SoLoader::ReloadLibrary() {
    if (libraryHandle) {
        UnloadLibrary();
    }

    LoadLibrary();
}

void SoLoader::LoadLibrary() {
    libraryHandle = dlopen(libraryFile.c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (!libraryHandle) {
        throw GLOVE_EXCEPTION((boost::format("Failed to load SO library %1%: %2%") % libraryFile % dlerror()).str());
    }
}

void SoLoader::UnloadLibrary() {
    if (!libraryHandle) {
        LOG(logger, warning,
            (boost::format("Unloading %1% but it had been unloaded earlier...") % libraryHandle).str());
        return;
    }

    if (dlclose(libraryHandle)) {
        LOG(logger, error, (boost::format("Failed to unload SO library %1%: %2%") % libraryHandle % dlerror()).str());
    }
}
}

#endif
