#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/services/Service.hpp"

namespace BlueDwarf {
class BD_API_EXPORT BasicService : public Service {
  public:
    BasicService(const ServiceType& serviceType);

    virtual bool NeedsInitialization();
    virtual bool Init(ServiceRegistry& serviceRegistry);
    virtual ServiceType GetType();

  private:
    const ServiceType serviceType;
};
}