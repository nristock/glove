#include "glove/filesystem/exceptions/StreamErrorException.hpp"

namespace glove {

StreamErrorException::StreamErrorException(std::string message, char const* file, int line)
    : GloveException(message, file, line) {
}
}