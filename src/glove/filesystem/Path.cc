#include "glove/filesystem/Path.hpp"

namespace BlueDwarf {

Path::Path() : path() {
}

Path::Path(const Path& other) : path(other.path) {
}

Path::Path(Path&& other) : path(std::move(other.path)) {
}

Path::Path(const std::string& path) : path(path) {
}

Path::Path(const char* path) : path(path) {
}

Path Path::Join(const Path& prefix, const Path& suffix) {
    if (prefix.path.back() == '/') {
        return Path(prefix.path + suffix.path);
    } else {
        return Path(prefix.path + "/" + suffix.path);
    }
}

std::string Path::StringJoin(const Path& prefix, const Path& suffix) {
    if (prefix.path.back() == '/') {
        return prefix.path + suffix.path;
    } else {
        return prefix.path + "/" + suffix.path;
    }
}

std::string Path::StringJoin(const Path& prefix, const std::string& suffix) {
    if (prefix.path.back() == '/') {
        return prefix.path + suffix;
    } else {
        return prefix.path + "/" + suffix;
    }
}

std::string Path::ToString() const {
    return path;
}

bool Path::IsEmpty() const {
    return path.empty();
}

bool Path::HasExtension() const {
    return !GetExtension().empty();
}

bool Path::IsAbsolute() const {
    return path.front() == '/';
}

bool Path::IsRelative() const {
    return !IsAbsolute();
}

bool Path::IsRelativePathSpecifier() const {
    if (path.length() == 1 && path.front() == '.') {
        return true;
    }

    return path.length() == 2 && path.front() == '.' && path.back() == '.';
}

std::string Path::GetFilename() const {
    if (IsEmpty()) {
        return std::string();
    }

    if(path.back() == '/') {
        return std::string(".");
    }

    std::size_t lastPathSeparator = path.rfind('/');
    if (lastPathSeparator == std::string::npos) {
        return path;
    }

    return path.substr(lastPathSeparator + 1);
}

std::string Path::GetExtension() const {
    std::string filename = GetFilename();

    if (Path(filename).IsRelativePathSpecifier()) {
        return std::string();
    }

    std::size_t lastDot = filename.rfind('.');
    if (lastDot == std::string::npos || lastDot == 0) {
        return std::string();
    }

    return filename.substr(lastDot);
}

std::string Path::GetFilenameWithoutExtension() const {
    std::string filename = GetFilename();
    std::string extension = GetExtension();

    if (extension.empty()) {
        return filename;
    }

    std::size_t lastDot = filename.rfind('.');
    return filename.substr(0, lastDot);
}

Path Path::GetParentPath() const {
    std::size_t lastSlash = path.rfind('/', path.length() - 2);
    if (lastSlash == 0 || lastSlash == std::string::npos) {
        return Path();
    }

    return path.substr(0, lastSlash + 1);
}

Path Path::GetCommonPrefix(const Path& other) const {
    return Path(std::string(path.begin(), std::mismatch(path.begin(), path.end(), other.path.begin(), other.path.end()).first));
}

template <> bool Path::operator==(const Path& other) const {
    return path == other.path;
}

template <> bool Path::operator!=(const Path& other) const {
    return !operator==(other);
}

Path Path::operator+(Path const& other) const {
    return Path::Join(*this, other);
}

Path& Path::operator+=(Path const& other) {
    if (path.back() == '/') {
        path += other.path;
    } else {
        path += "/" + other.path;
    }

    return *this;
}

bool Path::operator<(const Path& other) const {
    return path < other.path;
}

Path::operator std::string() const {
    return ToString();
}

bool operator==(const std::string& lhs, const Path& path) {
    return lhs == path.path;
}

bool operator!=(const std::string& lhs, const Path& path) {
    return !operator==(lhs, path);
}

bool operator==(const char* lhs, const Path& path) {
    return lhs == path.path;
}

bool operator!=(const char* lhs, const Path& path) {
    return !operator==(lhs, path);
}

std::ostream& operator<<(std::ostream& stream, const BlueDwarf::Path& rhs) {
    stream << static_cast<std::string>(rhs);
    return stream;
}
}