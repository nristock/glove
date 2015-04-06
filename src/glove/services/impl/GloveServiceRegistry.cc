#include "glove/GloveConfig.hpp"
#include "glove/utils/DebugUtils.hpp"
#include "glove/services/impl/GloveServiceRegistry.hpp"
#include "glove/services/exceptions/ServiceNotFound.hpp"
#include "glove/services/exceptions/ServiceNotInitialized.hpp"

namespace glove {

GloveServiceRegistry::GloveServiceRegistry() : GloveServiceRegistry(false) {
}

GloveServiceRegistry::GloveServiceRegistry(bool deferServiceInitialization) : deferServiceInitialization(deferServiceInitialization) {
    services.reserve(GLOVE_SERVICES_EXPECTED_SERVICE_COUNT);
}

void GloveServiceRegistry::RegisterService(const ServiceHandle& service) {
    if(Check(!ProvidesService(service->GetType()))) {
        services.emplace_back(service);

        L_INFO(fmt::format("Registered service: {0}", service->GetType()));

        if(service->NeedsInitialization() && !deferServiceInitialization) {
            RunServiceInitPass();
        }
    }
}

ServiceHandle GloveServiceRegistry::FindService(const ServiceType& serviceType) {
    auto serviceAndState = FindServiceAndState(serviceType);
    return serviceAndState.service;
}

bool GloveServiceRegistry::ProvidesService(const ServiceType& serviceType) {
    auto serviceAndState = FindServiceAndState(serviceType);
    return serviceAndState.IsValid();
}

void GloveServiceRegistry::InitAllServices() {
    TryInitAllServices(static_cast<int>(services.size()));

    auto iter = std::find_if(services.begin(), services.end(), [](const ServiceAndState& serviceAndState) {
       return !serviceAndState.isInitialized;
    });

    DebugAssert(iter == services.end());
}

void GloveServiceRegistry::TryInitAllServices(int maxPasses) {
    for(auto currentPass = 0; currentPass < maxPasses; ++currentPass) {
        if(!RunServiceInitPass()) {
            return;
        }
    }
}

bool GloveServiceRegistry::RunServiceInitPass() {
    bool serviceHasBeenInitialized = false;

    for(auto& serviceAndState : services) {
        if(!serviceAndState.isInitialized) {
            serviceHasBeenInitialized |= serviceAndState.TryInit(*this);
        }
    }

    return serviceHasBeenInitialized;
}

ServiceHandle GloveServiceRegistry::GetService(const ServiceType& serviceType) {
    auto serviceAndState = FindServiceAndState(serviceType);

    if(!serviceAndState.IsValid()) {
        GLOVE_THROW(ServiceNotFound, serviceType);
    }

    if(!serviceAndState.isInitialized) {
        GLOVE_THROW(ServiceNotInitialized, serviceType);
    }

    return serviceAndState.service;
}

bool GloveServiceRegistry::ProvidesInitializedService(const ServiceType& serviceType) {
    auto serviceAndState = FindServiceAndState(serviceType);
    return serviceAndState.isInitialized;
}

GloveServiceRegistry::ServiceAndState GloveServiceRegistry::FindServiceAndState(const ServiceType& serviceType) {
    auto iter = std::find_if(services.begin(), services.end(), [&](const ServiceAndState& serviceAndState) {
        return serviceAndState.IsValid() && (serviceAndState.service->GetType() == serviceType);
    });

    if(iter == services.end()) {
        return ServiceAndState();
    } else {
        return *iter;
    }
}

void GloveServiceRegistry::DeferServiceInitialization(bool deferInit) {
    deferServiceInitialization = deferInit;
}
}