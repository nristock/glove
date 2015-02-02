#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/filesystem/Filesystem.hpp"
#include "glove/filesystem/Path.hpp"

namespace glove {

class File {
public:
    File(const Path& filePath);
    File(const Path& filePath, const FilesystemAccessorHandle& filesystemAccessor);

    GLOVE_INLINE bool IsDirectory() const;
    GLOVE_INLINE bool IsRegularFile() const;
    GLOVE_INLINE bool Exists() const;

    GLOVE_INLINE const Path& GetPath() const;
    GLOVE_INLINE const FilesystemAccessorHandle& GetFilesystem() const;

private:
    const Path filePath;
    const FilesystemAccessorHandle filesystemAccessor;
};

} /* namespace glove */