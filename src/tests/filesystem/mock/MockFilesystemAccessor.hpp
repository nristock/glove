#pragma once

#include <vendor/gmock/gmock.h>
#include <string>

#include "core/filesystem/FileInfo.hpp"
#include "core/filesystem/IFilesystemAccessor.hpp"

namespace glove {

class FilesystemAccessorMock : public IFilesystemAccessor  {
public:
    static const std::string SEPARATOR;

    MOCK_METHOD1(GetFileInfo, const FileInfo(const std::string& path));
};

} /* namespace glove */