#pragma once

#include <boost/format.hpp>

#include "glove/BlueDwarfApi.hpp"
#include "glove/DwarfException.hpp"

namespace BlueDwarf {

class BD_API_EXPORT SymbolNotFound : public DwarfException {
  public:
    SymbolNotFound(const std::string& libName, const std::string& symbolName, char const* file, int line)
            : DwarfException((boost::format("Couldn't find symbol '%1%' in '%2%'") % symbolName % libName).str(), file, line) {}
};

} /* namespace BlueDwarf */