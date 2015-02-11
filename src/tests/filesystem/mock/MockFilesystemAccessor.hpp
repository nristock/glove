#pragma once

#include <gmock/gmock.hpp>
#include <string>
#include <istream>
#include <ostream>

#include <glove/filesystem/FileInfo.hpp>
#include <glove/filesystem/IFilesystem.hpp>
#include <glove/filesystem/Path.hpp>

namespace glove {

class FilesystemAccessorMock : public IFilesystem {
public:
    MOCK_METHOD1(GetFileInfo, const FileInfo(const Path& path));
    MOCK_METHOD1(CreateFileReadStream, std::istream*(const Path& path));
    MOCK_METHOD1(CreateFileWriteStream, std::ostream*(const Path& path));
};

} /* namespace glove */