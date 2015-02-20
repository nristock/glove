#pragma once

#include "glove/GloveApi.hpp"
#include "glove/services/ServiceRegistry.hpp"

namespace glove {

class GLOVE_API_EXPORT Service {
  public:
    virtual ~Service() = default;

    virtual bool Init(ServiceRegistry& serviceRegistry) = 0;
    virtual ServiceType GetType() = 0;
};

} /* namespace glove */