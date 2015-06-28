#include <boost/format.hpp>

#include "glove/filesystem/exceptions/FileInfoQueryException.hpp"

namespace BlueDwarf {

FileInfoQueryException::FileInfoQueryException(const Path& path, const std::string& message, char const* source,
                                               int line)
    : DwarfException((boost::format("Error querying file information for %1%: %2%") % path.ToString() % message).str(),
                     source, line) {
}
}