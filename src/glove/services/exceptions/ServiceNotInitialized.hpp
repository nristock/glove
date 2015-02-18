#pragma once

#include <boost/format.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "glove/GloveApi.hpp"
#include "glove/GloveException.hpp"
#include "glove/services/Services.hpp"

namespace glove {

class GLOVE_API_EXPORT ServiceNotInitialized : public GloveException {
  public:
    ServiceNotInitialized(const ServiceType& serviceType, char const* file, int line)
            : GloveException((boost::format("Querying uninitialized servivce %1%") % serviceType).str(), file, line) {}
};

} /* namespace glove */