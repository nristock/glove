#pragma once

#include <regex>

#include "glove/GloveFwd.hpp"

namespace glove {

class Path {
  private:
    static GLOVE_INLINE std::string StringJoin(const Path& prefix, const Path& suffix);
    static GLOVE_INLINE std::string StringJoin(const Path& prefix, const std::string& suffix);
    template <typename T, typename... Others>
    static GLOVE_INLINE std::string StringJoin(const T& prefix, const Others&... suffixes) {
        return Path::StringJoin(prefix, Path::StringJoin(suffixes...));
    }

  public:
    static GLOVE_INLINE Path Join(const Path& prefix, const Path& suffix);
    template <typename... Paths> static GLOVE_INLINE Path Join(const Paths&... paths) {
        // Use Path joining functions returning strings instead of paths to prevent creating unnecessary intermediate
        // Path objects.
        return Path(StringJoin(paths...));
    }

    Path(const Path& other);
    Path(Path&& other);
    Path();
    Path(const std::string& path);
    Path(const char* path);

    GLOVE_INLINE bool IsEmpty() const;
    GLOVE_INLINE bool HasExtension() const;
    GLOVE_INLINE bool IsAbsolute() const;
    GLOVE_INLINE bool IsRelative() const;

    /// Checks whether the path is '.' or '..' without constructing rvalue std::string objects
    /// \return Returns path == "." || path == ".."
    GLOVE_INLINE bool IsRelativePathSpecifier() const;

    GLOVE_INLINE std::string GetExtension() const;
    GLOVE_INLINE std::string GetFilename() const;
    GLOVE_INLINE std::string GetFilenameWithoutExtension() const;
    GLOVE_INLINE Path GetParentPath() const;

    GLOVE_INLINE friend bool operator==(const std::string& lhs, const glove::Path& rhs);
    GLOVE_INLINE friend bool operator!=(const std::string& lhs, const glove::Path& rhs);
    GLOVE_INLINE friend bool operator==(const char* lhs, const glove::Path& rhs);
    GLOVE_INLINE friend bool operator!=(const char* lhs, const glove::Path& rhs);

    GLOVE_INLINE friend std::ostream& operator<<(std::ostream& stream, const glove::Path& rhs);

    template <typename T> GLOVE_INLINE bool operator==(const T& other) const { return other == path; }
    template <typename T> GLOVE_INLINE bool operator!=(const T& other) const { return !operator==(other); }

    GLOVE_INLINE Path operator+(const Path& other) const;
    GLOVE_INLINE Path& operator+=(const Path& other);

    GLOVE_INLINE std::string ToString() const;
    GLOVE_INLINE explicit operator std::string() const;

  private:
    std::string path;
};

template <> GLOVE_INLINE bool Path::operator==<Path>(const Path& other) const;
template <> GLOVE_INLINE bool Path::operator!=<Path>(const Path& other) const;

} /* namespace glove */