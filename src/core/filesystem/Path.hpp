#pragma once

#include <regex>

#include <core/GloveFwd.h>

#include "FileInfo.hpp"

#include "core/filesystem/Filesystem.hpp"

namespace glove {

class Path {
  public:
    template <class FileSystemAccessor = NativeFilesystemAccessor>
    static GLOVE_INLINE std::string Translate(const Path& path) {
        std::regex internalSeparatorPattern("/");
        return std::regex_replace(path.ToString(), internalSeparatorPattern, FileSystemAccessor::SEPARATOR,
                                  std::regex_constants::match_any);
    }

    static GLOVE_INLINE Path Join(const Path& prefix, const Path& suffix);

    Path(const std::string& path) : path(path) {}

    GLOVE_INLINE std::string ToString() const;

    GLOVE_INLINE bool operator==(const Path& other) const;
    GLOVE_INLINE bool operator!=(const Path& other) const;

  private:
    std::string path;
};

} /* namespace glove */