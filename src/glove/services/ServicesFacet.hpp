#pragma once

#include "glove/GloveApi.hpp"
#include "glove/application/GloveApplication.hpp"
#include "glove/services/ServiceRegistry.hpp"


namespace glove {
class GLOVE_API_EXPORT ServicesFacet : public ApplicationFacet {
  public:
    ServicesFacet();
    ServicesFacet(ServiceRegistryHandle serviceRegistry);

    ServiceRegistryHandle GetServiceRegistry() const {return serviceRegistry;}
  private:
    ServiceRegistryHandle serviceRegistry;
};
}