#pragma once

#include "glove/GloveException.hpp"

namespace glove {

class GLOVE_API_EXPORT StreamErrorException : public GloveException {

public:
    StreamErrorException(std::string message, char const* file, int line);
};

} /* namespace glove */