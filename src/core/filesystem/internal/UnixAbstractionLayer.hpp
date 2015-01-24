#pragma once

#if defined(ON_UNIX)
#include <sys/stat.h>
#include <string>

#include "core/GloveFwd.h"

#include "core/filesystem/FileInfo.hpp"
#include "core/filesystem/IFilesystemAccessor.hpp"

namespace glove {

class UnixAbstractionLayer : public IFilesystemAccessor {
public:
    static const std::string SEPARATOR;

    GLOVE_INLINE const FileInfo GetFileInfo(const std::string& path);
};

} /* namespace glove */
#endif