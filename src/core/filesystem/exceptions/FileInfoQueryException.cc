#include "FileInfoQueryException.hpp"

#include <boost/format.hpp>

namespace glove {

FileInfoQueryException::FileInfoQueryException(const Path& path, const std::string& message, char const* source,
                                               int line)
    : GloveException((boost::format("Error querying file information for %1%: %2%") % path.ToString() % message).str(),
                     source, line) {
}
}