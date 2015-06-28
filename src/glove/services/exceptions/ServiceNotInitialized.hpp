#pragma once

#include <boost/format.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "glove/BlueDwarfApi.hpp"
#include "glove/DwarfException.hpp"
#include "glove/services/Services.hpp"

namespace BlueDwarf {

class BD_API_EXPORT ServiceNotInitialized : public DwarfException {
  public:
    ServiceNotInitialized(const ServiceType& serviceType, char const* file, int line)
            : DwarfException((boost::format("Querying uninitialized servivce %1%") % serviceType).str(), file, line) {}
};

} /* namespace BlueDwarf */