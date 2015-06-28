#include "glove/GloveConfig.hpp"
#include "glove/utils/DebugUtils.hpp"
#include "DwarfServiceRegistry.hpp"
#include "glove/services/exceptions/ServiceNotFound.hpp"
#include "glove/services/exceptions/ServiceNotInitialized.hpp"

namespace BlueDwarf {

DwarfServiceRegistry::DwarfServiceRegistry() : DwarfServiceRegistry(false) {
}

DwarfServiceRegistry::DwarfServiceRegistry(bool deferServiceInitialization) : deferServiceInitialization(deferServiceInitialization) {
    services.reserve(BD_SERVICES_EXPECTED_SERVICE_COUNT);
}

void DwarfServiceRegistry::RegisterService(const ServiceHandle& service) {
    if(Check(!ProvidesService(service->GetType()))) {
        services.emplace_back(service);

        L_INFO(fmt::format("Registered service: {0}", service->GetType()));

        if(service->NeedsInitialization() && !deferServiceInitialization) {
            RunServiceInitPass();
        }
    }
}

ServiceHandle DwarfServiceRegistry::FindService(const ServiceType& serviceType) {
    auto serviceAndState = FindServiceAndState(serviceType);
    return serviceAndState.service;
}

bool DwarfServiceRegistry::ProvidesService(const ServiceType& serviceType) {
    auto serviceAndState = FindServiceAndState(serviceType);
    return serviceAndState.IsValid();
}

void DwarfServiceRegistry::InitAllServices() {
    TryInitAllServices(static_cast<int>(services.size()));

    auto iter = std::find_if(services.begin(), services.end(), [](const ServiceAndState& serviceAndState) {
       return !serviceAndState.isInitialized;
    });

    DebugAssert(iter == services.end());
}

void DwarfServiceRegistry::TryInitAllServices(int maxPasses) {
    for(auto currentPass = 0; currentPass < maxPasses; ++currentPass) {
        if(!RunServiceInitPass()) {
            return;
        }
    }
}

bool DwarfServiceRegistry::RunServiceInitPass() {
    bool serviceHasBeenInitialized = false;

    for(auto& serviceAndState : services) {
        if(!serviceAndState.isInitialized) {
            serviceHasBeenInitialized |= serviceAndState.TryInit(*this);
        }
    }

    return serviceHasBeenInitialized;
}

ServiceHandle DwarfServiceRegistry::GetService(const ServiceType& serviceType) {
    auto serviceAndState = FindServiceAndState(serviceType);

    if(!serviceAndState.IsValid()) {
        DWARF_THROW(ServiceNotFound, serviceType);
    }

    if(!serviceAndState.isInitialized) {
        DWARF_THROW(ServiceNotInitialized, serviceType);
    }

    return serviceAndState.service;
}

bool DwarfServiceRegistry::ProvidesInitializedService(const ServiceType& serviceType) {
    auto serviceAndState = FindServiceAndState(serviceType);
    return serviceAndState.isInitialized;
}

DwarfServiceRegistry::ServiceAndState DwarfServiceRegistry::FindServiceAndState(const ServiceType& serviceType) {
    auto iter = std::find_if(services.begin(), services.end(), [&](const ServiceAndState& serviceAndState) {
        return serviceAndState.IsValid() && (serviceAndState.service->GetType() == serviceType);
    });

    if(iter == services.end()) {
        return ServiceAndState();
    } else {
        return *iter;
    }
}

void DwarfServiceRegistry::DeferServiceInitialization(bool deferInit) {
    deferServiceInitialization = deferInit;
}
}