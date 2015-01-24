#pragma once

#include <memory>

#if defined(ON_WINDOWS)
#include "core/filesystem/internal/WindowsAbstractionLayer.hpp"
#elif defined(ON_UNIX)
#include "core/filesystem/internal/UnixAbstractionLayer.hpp"
#endif

namespace glove {

class IFilesystemAccessor;
typedef std::shared_ptr<IFilesystemAccessor> FilesystemAccessorHandle;


#if defined(ON_WINDOWS)
typedef WindowsAbstractionLayer NativeFilesystemAccessor;
#elif defined(ON_UNIX)
typedef UnixAbstractionLayer NativeFilesystemAccessor;
#endif

} /* namespace glove */