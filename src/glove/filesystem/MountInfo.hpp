#pragma once

#include "glove/GloveApi.hpp"
#include "glove/filesystem/Filesystem.hpp"
#include "glove/filesystem/Path.hpp"

namespace glove {

class GLOVE_API_EXPORT MountInfo {
  public:
    MountInfo(FilesystemHandle const& filesystem, Path const& mountLocation)
            : filesystem(filesystem), mountLocation(mountLocation) {}


    const FilesystemHandle& GetFilesystem() const {
        return filesystem;
    }

    const Path& GetMountLocation() const {
        return mountLocation;
    }

  private:
    const FilesystemHandle filesystem;
    const Path mountLocation;
};

} /* namespace glove */