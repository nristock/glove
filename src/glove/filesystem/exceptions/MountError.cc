#include <boost/format.hpp>

#include "glove/filesystem/exceptions/MountError.hpp"

namespace BlueDwarf {

MountError::MountError(const std::string& message, char const* file, int line)
    : DwarfException(message, file, line) {
}
}