#include "Path.hpp"

#include "core/filesystem/Filesystem.hpp"

namespace glove {
bool Path::operator!=(const Path& other) const {
    return !operator==(other);
}

bool Path::operator==(const Path& other) const {
    return path == other.path;
}

std::string Path::ToString() const {
    return path;
}

Path Path::Join(const Path& prefix, const Path& suffix) {
    return Path(prefix.path + "/" + suffix.path);
}
}