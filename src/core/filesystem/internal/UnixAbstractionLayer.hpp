#pragma once

#if defined(ON_UNIX)
#include <sys/stat.h>
#include <string>

#include "core/GloveFwd.h"

#include "core/filesystem/FileInfo.hpp"
#include "core/filesystem/IFilesystem.hpp"
#include "core/filesystem/Path.hpp"

namespace glove {

/// A UNIX/POSIX native filsystem abstraction layer with the ability to be rooted to a specific directory.
/// The root directory path will be prepended to all filesystem queries.
/// E.g.: \code{.cpp}
/// UnixAbstractionLayer filesystem("/opt/install")
/// Path aPath("/somefile");
/// filesystem.GetFileInfo(aPath); // Will actually be executed on "/opt/install/somefile"
/// \endcode
/// The filesystem root defaults to the executable's directory.
class UnixAbstractionLayer : public IFilesystem {
public:
    UnixAbstractionLayer();
    UnixAbstractionLayer(const std::string& nativeRoot);

    /// Translates \p path to the corresponding native filesystem path
    GLOVE_INLINE Path MakePathNativeAbsolute(const Path& path);

    GLOVE_INLINE const FileInfo GetFileInfo(const Path& path) override;
    virtual std::istream* CreateFileReadStream(const Path& path) override;
    virtual std::ostream* CreateFileWriteStream(const Path& path) override;

private:
    std::string nativeRoot;
};

} /* namespace glove */
#endif