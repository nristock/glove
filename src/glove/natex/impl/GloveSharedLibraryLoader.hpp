#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/natex/SharedLibraryLoader.hpp"
#include "glove/natex/impl/UnixSharedLibrary.hpp"

namespace BlueDwarf {

template<class T>
class BD_API_EXPORT GenericSharedLibraryLoader : public SharedLibraryLoader {
  public:
    virtual std::unique_ptr<SharedLibrary> LoadLibrary(const std::string& fileName) {
        return std::make_unique<T>(fileName);
    }
};

#if defined(ON_UNIX)
extern template class GenericSharedLibraryLoader<UnixSharedLibrary>;
using DwarfSharedLibraryLoader = GenericSharedLibraryLoader<UnixSharedLibrary>;
#elif defined(ON_WINDOWS)
extern template class GenericSharedLibraryLoader<WindowsSharedLibrary>;
using DwarfSharedLibraryLoader = GenericSharedLibraryLoader<WindowsSharedLibrary>;
#endif

} /* namespace BlueDwarf */