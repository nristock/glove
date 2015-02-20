#pragma once

#include "glove/GloveApi.hpp"
#include "glove/services/Service.hpp"

namespace glove {
class GLOVE_API_EXPORT BasicService : public Service {
  public:
    BasicService(const ServiceType& serviceType);

    virtual bool Init(ServiceRegistry& serviceRegistry);
    virtual ServiceType GetType();

  private:
    const ServiceType serviceType;
};
}