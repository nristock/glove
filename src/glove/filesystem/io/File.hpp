#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/filesystem/Filesystem.hpp"
#include "glove/filesystem/Path.hpp"

namespace glove {

class File {
public:
    File(const Path& filePath);
    File(const Path& filePath, const FilesystemAccessorHandle& filesystemAccessor);

    bool IsDirectory() const;
    bool IsRegularFile() const;
    bool Exists() const;

    const Path& GetPath() const;
    const FilesystemAccessorHandle& GetFilesystem() const;

private:
    const Path filePath;
    const FilesystemAccessorHandle filesystemAccessor;
};

} /* namespace glove */