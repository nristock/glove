#pragma once

#include <boost/format.hpp>

#include "glove/GloveApi.hpp"
#include "glove/GloveException.hpp"

namespace glove {

class GLOVE_API_EXPORT SharedLibraryLoadFailed : public GloveException {
  public:
    SharedLibraryLoadFailed(const std::string& fileName, const std::string& reason, char const* file, int line)
            : GloveException((boost::format("Failed to load library file %1%: %2%") % fileName % reason).str(), file, line) {}
};

} /* namespace glove */