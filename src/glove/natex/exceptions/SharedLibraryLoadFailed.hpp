#pragma once

#include <boost/format.hpp>

#include "glove/BlueDwarfApi.hpp"
#include "glove/DwarfException.hpp"

namespace BlueDwarf {

class BD_API_EXPORT SharedLibraryLoadFailed : public DwarfException {
  public:
    SharedLibraryLoadFailed(const std::string& fileName, const std::string& reason, char const* file, int line)
            : DwarfException((boost::format("Failed to load library file %1%: %2%") % fileName % reason).str(), file, line) {}
};

} /* namespace BlueDwarf */