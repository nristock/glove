#pragma once

#include <map>

#include "glove/GloveApi.hpp"
#include "glove/filesystem/Filesystem.hpp"
#include "glove/filesystem/Path.hpp"
#include "glove/filesystem/IFilesystem.hpp"
#include "glove/filesystem/MountInfo.hpp"

namespace glove {

class GLOVE_API_EXPORT MountAwareFilesystem : public IFilesystem {
  public:
    void Mount(const Path& path, const FilesystemHandle& filesystem);
    void Unmount(const Path& path);

    std::size_t GetMountCount();

  protected:
    MountInfo ResolveToMount(const Path& path);
    Path CalculateMountRelativePath(const MountInfo& mountInfo, const Path& path);

  private:
    typedef std::map<Path, FilesystemHandle> MountMap;
    MountMap mountMap;
};

} /* namespace glove */