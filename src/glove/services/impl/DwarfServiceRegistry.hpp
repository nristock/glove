#pragma once

#include <vector>
#include <unordered_map>

#include "glove/BlueDwarfApi.hpp"
#include "glove/utils/DebugUtils.hpp"
#include "glove/services/Services.hpp"
#include "glove/services/ServiceRegistry.hpp"
#include "glove/services/Service.hpp"

namespace BlueDwarf {

/// \brief The default service registry.
///
/// This registry allows to register a single service implementation per service type.
/// Service initialization is done using initialization passes. In each pass the registry will iterate over all services
/// and try to initialize currently uninitialized services. While this approach has O(n) worst-case complexity, it
/// allows the engine to keep the service system as lightweight as possible by saving building dependency graphs and
/// implementing a topological sorting algorithm.
/// Services can signal the registry whether their initialization was successful or not. See \link BlueDwarf::Service. The
/// registry will keep running init passes until either all registered services are initialized or no new service got
/// initialized during a pass.
class BD_API_EXPORT DwarfServiceRegistry : public ServiceRegistry {
  public:
    DwarfServiceRegistry();
    DwarfServiceRegistry(bool deferServiceInitialization);

    virtual void RegisterService(const ServiceHandle& service);
    virtual ServiceHandle FindService(const ServiceType& serviceType);
    virtual ServiceHandle GetService(const ServiceType& serviceType);
    virtual bool ProvidesService(const ServiceType& serviceType);
    virtual bool ProvidesInitializedService(const ServiceType& serviceType);

    virtual void InitAllServices();

    void DeferServiceInitialization(bool deferInitialization);

  private:
    /// \brief This structure combines a service's init-state with its handle.
    struct ServiceAndState {
        ServiceAndState() : isInitialized(false), service() {}
        ServiceAndState(ServiceHandle service) : isInitialized(!service->NeedsInitialization()), service(std::move(service)) {};
        ServiceAndState(const ServiceAndState& other) : isInitialized(other.isInitialized), service(other.service) {}
        ServiceAndState(ServiceAndState&& other) : isInitialized(std::move(other.isInitialized)), service(std::move(other.service)) {}

        bool isInitialized;
        ServiceHandle service;

        /// \brief Calls the service's Init method iff service is a valid handle.
        /// Note: This function does not prevent double-init, it does however do a debug check.
        inline bool TryInit(ServiceRegistry& serviceRegistry) {
            Check(!isInitialized);
            Check(IsValid());

            if(IsValid() && service->Init(serviceRegistry)) {
                isInitialized = true;
            }

            return isInitialized;
        }

        inline bool IsValid() const {
            return (bool)service;
        }
    };

    using ServiceCollection = std::vector<ServiceAndState>;

    /// \brief Tries to initialize all services in maxPasses initialization passes.
    void TryInitAllServices(int maxPasses);
    /// \brief Iterates all registered services and tries to initialize the uninitialized ones.
    bool RunServiceInitPass();
    /// \brief Tries to find a service entry in the internal list of registered services.
    ServiceAndState FindServiceAndState(const ServiceType& serviceType);

    /// \brief If set to true, RegisterService will not invoke an initialization pass.
    bool deferServiceInitialization;
    /// \brief The internal list of registered services and their states stored using a StateAndService.
    ServiceCollection services;
};

} /* namespace BlueDwarf */