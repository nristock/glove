#pragma once

#include <boost/format.hpp>

#include "glove/GloveApi.hpp"
#include "glove/GloveException.hpp"

namespace glove {

class GLOVE_API_EXPORT SymbolNotFound : public GloveException {
  public:
    SymbolNotFound(const std::string& libName, const std::string& symbolName, char const* file, int line)
            : GloveException((boost::format("Couldn't find symbol '%1%' in '%2%'") % symbolName % libName).str(), file, line) {}
};

} /* namespace glove */