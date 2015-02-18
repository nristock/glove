#pragma once

#include <boost/format.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "glove/GloveApi.hpp"
#include "glove/GloveException.hpp"
#include "glove/services/Services.hpp"

namespace glove {

class GLOVE_API_EXPORT ServiceNotFound : public GloveException {
  public:
    ServiceNotFound(const ServiceType& serviceType, char const* file, int line)
        : GloveException((boost::format("Unable to find service %1%") % serviceType).str(), file, line) {}
};

} /* namespace glove */