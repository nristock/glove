#pragma once

#include <string>

#include "glove/GloveApi.hpp"

namespace glove {

class GLOVE_API_EXPORT FileInfo {
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

    bool operator==(const FileInfo& other) const {
        return size == other.size && type == other.type;
    }

private:
    const FileType type;
    const std::size_t size;
};
} /* namespace glove */