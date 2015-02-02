#include "InvalidFileTypeException.hpp"

namespace glove {

InvalidFileTypeException::InvalidFileTypeException(std::string& message, char const* file, int line)
    : GloveException(message, file, line) {
}
}