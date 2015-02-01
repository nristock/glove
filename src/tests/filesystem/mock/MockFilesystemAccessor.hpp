#pragma once

#include <vendor/gmock/gmock.h>
#include <string>
#include <istream>
#include <ostream>

#include "core/filesystem/FileInfo.hpp"
#include "core/filesystem/IFilesystem.hpp"
#include "core/filesystem/Path.hpp"

namespace glove {

class FilesystemAccessorMock : public IFilesystem {
public:
    MOCK_METHOD1(GetFileInfo, const FileInfo(const Path& path));
    MOCK_METHOD1(CreateFileReadStream, std::istream*(const Path& path));
    MOCK_METHOD1(CreateFileWriteStream, std::ostream*(const Path& path));
};

} /* namespace glove */