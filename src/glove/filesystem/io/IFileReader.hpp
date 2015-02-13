#pragma once

#include <cstddef>

#include "glove/GloveApi.hpp"

namespace glove {

class GLOVE_API_EXPORT IFileReader {
public:
    virtual ~IFileReader() = default;

    virtual void Read(void* destination, std::size_t size) = 0;
};

} /* namespace glove */