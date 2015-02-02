#pragma once

#include <string>
#include <sys/wait.h>

namespace glove {

class FileInfo {
public:
    enum class FileType {
        UNKNOWN, NOT_FOUND, REGULAR, DIRECTORY
    };

    FileInfo(const FileType& type, const size_t size) : type(type), size(size) {}

    FileType GetType() const {
        return type;
    }

    std::size_t GetSize() const {
        return size;
    }

private:
    const FileType type;
    const std::size_t size;
};

} /* namespace glove */