#pragma once

#include <memory>

namespace glove {

class IFilesystem;
typedef std::shared_ptr<IFilesystem> FilesystemAccessorHandle;

typedef std::unique_ptr<std::istream> InputStreamHandle;
typedef std::unique_ptr<std::ostream> OutputStreamHandle;


#if defined(ON_WINDOWS)
class WindowsAbstractionLayer;
typedef WindowsAbstractionLayer NativeFilesystemAccessor;
#elif defined(ON_UNIX)
class UnixAbstractionLayer;
typedef UnixAbstractionLayer NativeFilesystemAccessor;
#endif

} /* namespace glove */

#if defined(ON_WINDOWS)
#include "glove/filesystem/internal/WindowsAbstractionLayer.hpp"
#elif defined(ON_UNIX)
#include "glove/filesystem/internal/UnixAbstractionLayer.hpp"
#endif