#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/application/DwarfApplication.hpp"
#include "glove/services/ServiceRegistry.hpp"


namespace BlueDwarf {
class BD_API_EXPORT ServicesFacet : public ApplicationFacet {
  public:
    ServicesFacet();
    ServicesFacet(ServiceRegistryHandle serviceRegistry);

    ServiceRegistryHandle GetServiceRegistry() const {return serviceRegistry;}
  private:
    ServiceRegistryHandle serviceRegistry;
};
}