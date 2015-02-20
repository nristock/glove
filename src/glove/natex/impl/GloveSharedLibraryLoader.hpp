#pragma once

#include "glove/GloveApi.hpp"
#include "glove/natex/SharedLibraryLoader.hpp"
#include "glove/natex/impl/UnixSharedLibrary.hpp"

namespace glove {

template<class T>
class GLOVE_API_EXPORT GenericSharedLibraryLoader : public SharedLibraryLoader {
  public:
    virtual std::unique_ptr<SharedLibrary> LoadLibrary(const std::string& fileName) {
        return std::make_unique<T>(fileName);
    }
};

#if defined(ON_UNIX)
extern template class GenericSharedLibraryLoader<UnixSharedLibrary>;
using GloveSharedLibraryLoader = GenericSharedLibraryLoader<UnixSharedLibrary>;
#elif defined(ON_WINDOWS)
extern template class GenericSharedLibraryLoader<WindowsSharedLibrary>;
using GloveSharedLibraryLoader = GenericSharedLibraryLoader<WindowsSharedLibrary>;
#endif

} /* namespace glove */