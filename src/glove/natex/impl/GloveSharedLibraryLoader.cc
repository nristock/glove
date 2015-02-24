#include "glove/natex/impl/GloveSharedLibraryLoader.hpp"

namespace glove {
#if defined(ON_UNIX)
template class GenericSharedLibraryLoader<UnixSharedLibrary>;
#elif defined(ON_WINDOWS)
template class GenericSharedLibraryLoader<WindowsSharedLibrary>;
#endif
}