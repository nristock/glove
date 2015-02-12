#include <boost/format.hpp>

#include "glove/filesystem/exceptions/MountError.hpp"

namespace glove {

MountError::MountError(const std::string& message, char const* file, int line)
    : GloveException(message, file, line) {
}
}