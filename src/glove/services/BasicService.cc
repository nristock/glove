#include "glove/services/BasicService.hpp"

namespace glove {
BasicService::BasicService(ServiceType const &serviceType) : serviceType(serviceType) {
}

bool BasicService::NeedsInitialization() {
    return false;
}

bool BasicService::Init(ServiceRegistry& serviceRegistry) {
    return true;
}

ServiceType BasicService::GetType() {
    return serviceType;
}
}