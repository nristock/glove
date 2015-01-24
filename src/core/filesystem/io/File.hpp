#pragma once

#include "core/filesystem/Filesystem.hpp"
#include "core/filesystem/Path.hpp"

namespace glove {

class File {
public:
    File(const Path& filePath) : filePath(filePath), filesystemAccessor(new NativeFilesystemAccessor()) {}

    File(const Path& filePath, const FilesystemAccessorHandle& filesystemAccessor)
            : filePath(filePath), filesystemAccessor(filesystemAccessor) {}

    GLOVE_INLINE bool IsDirectory() const {
        return filesystemAccessor->GetFileInfo(filePath.ToString()).GetType() == FileInfo::FileType::DIRECTORY;
    }

    GLOVE_INLINE bool IsRegularFile() const {
        return filesystemAccessor->GetFileInfo(filePath.ToString()).GetType() == FileInfo::FileType::REGULAR;
    }

    GLOVE_INLINE bool Exists() const {
        return filesystemAccessor->GetFileInfo(filePath.ToString()).GetType() != FileInfo::FileType::NONE;
    }

    GLOVE_INLINE const Path& GetPath() const {
        return filePath;
    }

private:
    const Path filePath;
    FilesystemAccessorHandle filesystemAccessor;
};

} /* namespace glove */