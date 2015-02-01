#pragma once

#include <core/filesystem/Filesystem.hpp>
#include "core/filesystem/IFilesystem.hpp"
#include "core/filesystem/compression/Compression.hpp"
#include "core/filesystem/compression/ZipArchive.hpp"

namespace glove {
class ZipFilesystem : public IFilesystem {

  public:
    ZipFilesystem(const ZipArchiveHandle& zipArchive);

    template <class FilesystemAccessorType = NativeFilesystemAccessor>
    ZipFilesystem(const Path& path, const FilesystemAccessorHandle& filesystem) {
        // A little bit of hacking is required here since libzip doesn't allow to read zip files from memory.
        archive = ZipArchiveHandle(new ZipArchive(dynamic_cast<FilesystemAccessorType*>(filesystem.get())->MakePathNativeAbsolute(path)));
    }

    virtual ~ZipFilesystem();

    virtual const FileInfo GetFileInfo(const Path& path);
    virtual std::istream* CreateFileReadStream(const Path& path);
    virtual std::ostream* CreateFileWriteStream(const Path& path);

  private:
    ZipArchiveHandle archive;
};
}