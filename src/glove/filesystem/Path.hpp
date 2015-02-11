#pragma once

#include <regex>

#include "glove/GloveFwd.hpp"

namespace glove {

class Path {
  private:
    static std::string StringJoin(const Path& prefix, const Path& suffix);
    static std::string StringJoin(const Path& prefix, const std::string& suffix);
    template <typename T, typename... Others>
    static std::string StringJoin(const T& prefix, const Others&... suffixes) {
        return Path::StringJoin(prefix, Path::StringJoin(suffixes...));
    }

  public:
    static Path Join(const Path& prefix, const Path& suffix);
    template <typename... Paths> static Path Join(const Paths&... paths) {
        // Use Path joining functions returning strings instead of paths to prevent creating unnecessary intermediate
        // Path objects.
        return Path(StringJoin(paths...));
    }

    Path(const Path& other);
    Path(Path&& other);
    Path();
    Path(const std::string& path);
    Path(const char* path);

    bool IsEmpty() const;
    bool HasExtension() const;
    bool IsAbsolute() const;
    bool IsRelative() const;

    /// Checks whether the path is '.' or '..' without constructing rvalue std::string objects
    /// \return Returns path == "." || path == ".."
    bool IsRelativePathSpecifier() const;

    std::string GetExtension() const;
    std::string GetFilename() const;
    std::string GetFilenameWithoutExtension() const;
    Path GetParentPath() const;

    friend bool operator==(const std::string& lhs, const glove::Path& rhs);
    friend bool operator!=(const std::string& lhs, const glove::Path& rhs);
    friend bool operator==(const char* lhs, const glove::Path& rhs);
    friend bool operator!=(const char* lhs, const glove::Path& rhs);

    friend std::ostream& operator<<(std::ostream& stream, const glove::Path& rhs);

    template <typename T> bool operator==(const T& other) const { return other == path; }
    template <typename T> bool operator!=(const T& other) const { return !operator==(other); }

    Path operator+(const Path& other) const;
    Path& operator+=(const Path& other);

    std::string ToString() const;
    explicit operator std::string() const;

  private:
    std::string path;
};

template <> bool Path::operator==<Path>(const Path& other) const;
template <>  bool Path::operator!=<Path>(const Path& other) const;

} /* namespace glove */