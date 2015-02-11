#pragma once

#include "glove/GloveException.hpp"

namespace glove {

class InvalidFileTypeException : public GloveException {

public:
    InvalidFileTypeException(std::string& message, char const* file, int line);
};

} /* namespace glove */