#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/services/ServiceRegistry.hpp"

namespace BlueDwarf {

class BD_API_EXPORT Service {
  public:
    virtual ~Service() = default;

    virtual bool NeedsInitialization() = 0;
    virtual bool Init(ServiceRegistry& serviceRegistry) = 0;
    virtual ServiceType GetType() = 0;
};

} /* namespace BlueDwarf */