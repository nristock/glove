#pragma once

#include "glove/GloveException.h"

namespace glove {

class InvalidFileTypeException : public GloveException {

public:
    InvalidFileTypeException(std::string& message, char const* file, int line);
};

} /* namespace glove */