#include "glove/filesystem/exceptions/FileNotFoundException.hpp"
#include "glove/filesystem/FileInfo.hpp"
#include "glove/filesystem/Path.hpp"
#include "glove/filesystem/exceptions/MountError.hpp"
#include "glove/filesystem/inmemory/InMemoryFilesystem.hpp"

namespace BlueDwarf {

const FileInfo InMemoryFilesystem::GetFileInfo(const Path& path) {
    try {
        MountInfo targetMount = ResolveToMount(path);
        return targetMount.GetFilesystem()->GetFileInfo(CalculateMountRelativePath(targetMount, path));
    }  catch(const MountError& ex) {
        return FileInfo(FileInfo::FileType::NOT_FOUND, 0);
    }
}

std::istream* InMemoryFilesystem::CreateFileReadStream(const Path& path) {
    try {
        MountInfo targetMount = ResolveToMount(path);
        return targetMount.GetFilesystem()->CreateFileReadStream(CalculateMountRelativePath(targetMount, path));
    }  catch(const MountError& ex) {
        DWARF_THROW(FileNotFoundException, File(path, shared_from_this()));
    }
}

std::ostream* InMemoryFilesystem::CreateFileWriteStream(const Path& path) {
    try {
        MountInfo targetMount = ResolveToMount(path);
        return targetMount.GetFilesystem()->CreateFileWriteStream(CalculateMountRelativePath(targetMount, path));
    }  catch(const MountError& ex) {
        DWARF_THROW(FileNotFoundException, File(path, shared_from_this()));
    }
}
}