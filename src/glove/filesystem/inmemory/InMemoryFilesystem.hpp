#pragma once

#include "glove/GloveApi.hpp"
#include "glove/filesystem/MountAwareFilesystem.hpp"
#include "glove/filesystem/FileInfo.hpp"

namespace glove {

class GLOVE_API_EXPORT InMemoryFilesystem : public MountAwareFilesystem, public std::enable_shared_from_this<IFilesystem> {
  public:
    virtual const FileInfo GetFileInfo(const Path& path);
    virtual std::istream* CreateFileReadStream(const Path& path);
    virtual std::ostream* CreateFileWriteStream(const Path& path);
};

} /* namespace glove */