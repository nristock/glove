#pragma once

namespace glove {

class IFilesystemAccessor {
public:
    virtual ~IFilesystemAccessor() = default;

    virtual const FileInfo GetFileInfo(const std::string& path) = 0;
};

}