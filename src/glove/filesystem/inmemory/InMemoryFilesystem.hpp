#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/filesystem/MountAwareFilesystem.hpp"
#include "glove/filesystem/FileInfo.hpp"

namespace BlueDwarf {

class BD_API_EXPORT InMemoryFilesystem : public MountAwareFilesystem, public std::enable_shared_from_this<IFilesystem> {
  public:
    virtual const FileInfo GetFileInfo(const Path& path);
    virtual std::istream* CreateFileReadStream(const Path& path);
    virtual std::ostream* CreateFileWriteStream(const Path& path);
};

} /* namespace BlueDwarf */