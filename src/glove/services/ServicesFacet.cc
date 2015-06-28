#include "glove/services/ServicesFacet.hpp"
#include "glove/services/impl/GloveServiceRegistry.hpp"

namespace glove {

ServicesFacet::ServicesFacet() : ApplicationFacet("ServicesFacet"), serviceRegistry(new GloveServiceRegistry{}) {
}

ServicesFacet::ServicesFacet(ServiceRegistryHandle serviceRegistry) : serviceRegistry(std::move(serviceRegistry)) {
}
}