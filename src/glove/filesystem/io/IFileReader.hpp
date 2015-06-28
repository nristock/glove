#pragma once

#include <cstddef>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {

class BD_API_EXPORT IFileReader {
public:
    virtual ~IFileReader() = default;

    virtual void Read(void* destination, std::size_t size) = 0;
};

} /* namespace BlueDwarf */