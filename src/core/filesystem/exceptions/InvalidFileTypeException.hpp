#pragma once

#include <core/GloveException.h>

namespace glove {

class InvalidFileTypeException : public GloveException {

public:
    InvalidFileTypeException(std::string& message, char const* file, int line) : GloveException(message, file, line) {}
};

} /* namespace glove */