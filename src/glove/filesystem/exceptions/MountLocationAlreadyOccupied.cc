#include <boost/format.hpp>

#include "glove/filesystem/exceptions/MountLocationAlreadyOccupied.hpp"

namespace glove {

MountLocationAlreadyOccupied::MountLocationAlreadyOccupied(const Path& path, char const* file, int line)
    : MountError((boost::format("There's another filesystem already mounted at %1%") % path).str(), file, line) {
}
}