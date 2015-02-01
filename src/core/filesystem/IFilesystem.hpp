#pragma once

#include <istream>
#include <ostream>

#include "core/filesystem/Path.hpp"

namespace glove {

class IFilesystem {
public:
    virtual ~IFilesystem() = default;

    virtual const FileInfo GetFileInfo(const Path& path) = 0;
    virtual std::istream* CreateFileReadStream(const Path& path) = 0;
    virtual std::ostream* CreateFileWriteStream(const Path& path) = 0;
};

}