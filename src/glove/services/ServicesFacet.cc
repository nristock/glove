#include "glove/services/ServicesFacet.hpp"
#include "glove/services/impl/DwarfServiceRegistry.hpp"

namespace BlueDwarf {

ServicesFacet::ServicesFacet() : ApplicationFacet("ServicesFacet"), serviceRegistry(new DwarfServiceRegistry{}) {
}

ServicesFacet::ServicesFacet(ServiceRegistryHandle serviceRegistry) : serviceRegistry(std::move(serviceRegistry)) {
}
}