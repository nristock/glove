#pragma once

#include <memory>

namespace glove {

class IFilesystem;
typedef std::shared_ptr<IFilesystem> FilesystemHandle;

typedef std::unique_ptr<std::istream> InputStreamHandle;
typedef std::unique_ptr<std::ostream> OutputStreamHandle;


#if defined(ON_WINDOWS)
class WindowsAbstractionLayer;
typedef WindowsAbstractionLayer NativeFilesystemAccessor;
#elif defined(ON_UNIX)
class UnixNativeFilesystem;
typedef UnixNativeFilesystem NativeFilesystemAccessor;
#endif

} /* namespace glove */

#if defined(ON_WINDOWS)
#include "glove/filesystem/internal/WindowsNativeFilesystem.hpp"
#elif defined(ON_UNIX)
#include "glove/filesystem/internal/UnixNativeFilesystem.hpp"
#endif