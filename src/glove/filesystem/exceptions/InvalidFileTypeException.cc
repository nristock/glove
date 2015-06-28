#include "glove/filesystem/exceptions/InvalidFileTypeException.hpp"

namespace BlueDwarf {

InvalidFileTypeException::InvalidFileTypeException(std::string& message, char const* file, int line)
    : DwarfException(message, file, line) {
}
}