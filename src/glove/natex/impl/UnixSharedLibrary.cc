#include <dlfcn.h>

#include "glove/utils/DebugUtils.hpp"
#include "glove/natex/exceptions/SharedLibraryLoadFailed.hpp"
#include "glove/natex/exceptions/SymbolNotFound.hpp"
#include "glove/natex/impl/UnixSharedLibrary.hpp"

namespace BlueDwarf {

UnixSharedLibrary::UnixSharedLibrary(const std::string& fileName) : fileName(fileName), libraryHandle(nullptr) {
    LoadDso();
}

UnixSharedLibrary::~UnixSharedLibrary() {
    UnloadDso();
}

void* UnixSharedLibrary::GetSymbol(const std::string& symbolName) {
    void* symbolAddress = dlsym(libraryHandle, symbolName.c_str());

    if (symbolAddress == nullptr) {
        DWARF_THROW(SymbolNotFound, symbolName, fileName);
    }

    return symbolAddress;
}

void UnixSharedLibrary::LoadDso() {
    DebugAssert(libraryHandle == nullptr);

    libraryHandle = dlopen(fileName.c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (libraryHandle == nullptr) {
        DWARF_THROW(SharedLibraryLoadFailed, fileName, dlerror());
    }
}

void UnixSharedLibrary::UnloadDso() {
    DebugAssert(libraryHandle != nullptr);

    int closeResult = dlclose(libraryHandle);
    if (closeResult != 0) {
        logger.Error(fmt::format("Failed to unload SO library {0}: {1}", libraryHandle, dlerror()), M_TAG);
    }
}
}