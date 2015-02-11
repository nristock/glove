#include "glove/filesystem/io/File.hpp"
#include "glove/filesystem/IFilesystem.hpp"

namespace glove {

File::File(const Path& filePath)  : filePath(filePath), filesystemAccessor(new NativeFilesystemAccessor()) {}

File::File(const Path& filePath, const FilesystemAccessorHandle& filesystemAccessor)
        : filePath(filePath), filesystemAccessor(filesystemAccessor) {}

bool File::IsDirectory() const {
    return filesystemAccessor->GetFileInfo(filePath.ToString()).GetType() == FileInfo::FileType::DIRECTORY;
}

bool File::IsRegularFile() const {
    return filesystemAccessor->GetFileInfo(filePath.ToString()).GetType() == FileInfo::FileType::REGULAR;
}

bool File::Exists() const {
    return filesystemAccessor->GetFileInfo(filePath.ToString()).GetType() != FileInfo::FileType::NOT_FOUND;
}

const Path& File::GetPath() const {
    return filePath;
}

const FilesystemAccessorHandle& File::GetFilesystem() const {
    return filesystemAccessor;
}
}