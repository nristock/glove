#pragma once

#include "glove/GloveException.hpp"

namespace glove {

class GLOVE_API_EXPORT InvalidFileTypeException : public GloveException {

public:
    InvalidFileTypeException(std::string& message, char const* file, int line);
};

} /* namespace glove */