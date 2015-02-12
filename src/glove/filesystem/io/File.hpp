#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/filesystem/Filesystem.hpp"
#include "glove/filesystem/Path.hpp"

namespace glove {

class GLOVE_API_EXPORT File {
public:
    File(const Path& filePath);
    File(const Path& filePath, const FilesystemHandle& filesystemAccessor);

    bool IsDirectory() const;
    bool IsRegularFile() const;
    bool Exists() const;

    const Path& GetPath() const;
    const FilesystemHandle& GetFilesystem() const;

private:
    const Path filePath;
    const FilesystemHandle filesystem;
};

} /* namespace glove */