#pragma once

#include <core/GloveException.h>

namespace glove {

class StreamErrorException : public GloveException {

public:
    StreamErrorException(std::string message, char const* file, int line) : GloveException(message, file, line) {}
};

} /* namespace glove */