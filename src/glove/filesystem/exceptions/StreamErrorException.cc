#include "glove/filesystem/exceptions/StreamErrorException.hpp"

namespace BlueDwarf {

StreamErrorException::StreamErrorException(std::string message, char const* file, int line)
    : DwarfException(message, file, line) {
}
}