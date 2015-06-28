#include "glove/filesystem/io/File.hpp"
#include "glove/filesystem/IFilesystem.hpp"

namespace BlueDwarf {

File::File(const Path& filePath)  : filePath(filePath), filesystem(new NativeFilesystemAccessor()) {}

File::File(const Path& filePath, const FilesystemHandle& filesystemAccessor)
        : filePath(filePath), filesystem(filesystemAccessor) {}

bool File::IsDirectory() const {
    return filesystem->GetFileInfo(filePath.ToString()).GetType() == FileInfo::FileType::DIRECTORY;
}

bool File::IsRegularFile() const {
    return filesystem->GetFileInfo(filePath.ToString()).GetType() == FileInfo::FileType::REGULAR;
}

bool File::Exists() const {
    return filesystem->GetFileInfo(filePath.ToString()).GetType() != FileInfo::FileType::NOT_FOUND;
}

const Path& File::GetPath() const {
    return filePath;
}

const FilesystemHandle& File::GetFilesystem() const {
    return filesystem;
}
}