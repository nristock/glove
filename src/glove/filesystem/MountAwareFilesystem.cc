#include <boost/format.hpp>

#include "glove/filesystem/exceptions/FileNotFoundException.hpp"
#include "glove/GloveException.hpp"
#include "glove/filesystem/io/File.hpp"
#include "glove/filesystem/exceptions/MountLocationAlreadyOccupied.hpp"
#include "glove/filesystem/MountAwareFilesystem.hpp"

namespace glove {

void MountAwareFilesystem::Mount(const Path& path, const FilesystemHandle& filesystem) {
    if(path.IsRelative()) {
        GLOVE_THROW(MountError, (boost::format("Cannot mount at %1% because it is a relative path.") % path).str());
    }

    Path mountPath = path.GetFilename() == "." ? path : (path + "");

    if(mountMap.count(mountPath) > 0) {
        GLOVE_THROW(MountLocationAlreadyOccupied, mountPath);
    }

    mountMap.emplace(mountPath, filesystem);
}

void MountAwareFilesystem::Unmount(const Path& path) {
    if(path.IsRelative()) {
        GLOVE_THROW(MountError, (boost::format("Cannot unmount %1% because it is a relative path.") % path).str());
    }

    Path mountPath = path.GetFilename() == "." ? path : (path + "");
    if(mountMap.count(mountPath) == 0) {
        GLOVE_THROW(MountError, (boost::format("Cannot unmount %1% because it is not a mount location.") % mountPath).str());
    }

    mountMap.erase(mountPath);
}

std::size_t MountAwareFilesystem::GetMountCount() {
    return mountMap.size();
}

MountInfo MountAwareFilesystem::ResolveToMount(const Path& path) {
    if(path.IsRelative()) {
        GLOVE_THROW(MountError, (boost::format("Cannot resolve %1% because it is a relative path.") % path).str());
    }

    for(const std::pair<Path, FilesystemHandle>& mount : mountMap) {
        Path commonPrefix= path.GetCommonPrefix(mount.first);
        if(commonPrefix.GetFilename() != ".") {
            commonPrefix += "";
        }

        if(commonPrefix == mount.first) {
            return MountInfo(mount.second, mount.first);
        }
    }

    GLOVE_THROW(MountError, (boost::format("%1% doesn't match any mount.") % path).str());
}

Path MountAwareFilesystem::CalculateMountRelativePath(const MountInfo& mountInfo, const Path& other) {
    std::string filePathAsString = other.ToString();
    std::string mountPathAsString = mountInfo.GetMountLocation().ToString();
    return Path(std::string(std::mismatch(filePathAsString.begin(), filePathAsString.end(), mountPathAsString.begin(), mountPathAsString.end()).first - 1, filePathAsString.end()));
}
}