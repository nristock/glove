#pragma once

#include "glove/GloveException.hpp"

namespace glove {

class StreamErrorException : public GloveException {

public:
    StreamErrorException(std::string message, char const* file, int line);
};

} /* namespace glove */