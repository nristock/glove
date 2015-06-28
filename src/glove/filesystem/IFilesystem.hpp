#pragma once

#include <istream>
#include <ostream>

#include "glove/BlueDwarfApi.hpp"
#include "glove/filesystem/FileInfo.hpp"
#include "glove/filesystem/Path.hpp"

namespace BlueDwarf {

class BD_API_EXPORT IFilesystem {
public:
    virtual ~IFilesystem() = default;

    virtual const FileInfo GetFileInfo(const Path& path) = 0;
    virtual std::istream* CreateFileReadStream(const Path& path) = 0;
    virtual std::ostream* CreateFileWriteStream(const Path& path) = 0;
};

}