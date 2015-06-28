#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/services/Services.hpp"

namespace BlueDwarf {

class BD_API_EXPORT ServiceRegistry {
  public:
    virtual ~ServiceRegistry() = default;

    /// \brief Registers a service.
    ///
    /// Registering a service of an already registered type is a non fatal error and does not result in an exception.
    virtual void RegisterService(const ServiceHandle& service) = 0;

    /// \brief Tries to find a registered service of type @p serviceType.
    ///
    /// This function either returns a handle to a registered service or an empty (i.e. invalid/nullptr) service handle.
    /// The returned service is not guaranteed to be initialized. Use GetService instead to ensure initialization state.
    virtual ServiceHandle FindService(const ServiceType& serviceType) = 0;

    /// \brief Tries to find a registered and initialized service of type @p serviceType and throws an exception is no
    /// such service can be found.
    ///
    /// This method works like FindService but throws a ServiceNotFound exception if there is no service of @p serviceType
    /// registered. It can also throw a ServiceNotInitialized exception if the requested service type hasn't been
    /// initialized yet.
    virtual ServiceHandle GetService(const ServiceType& serviceType) = 0;

    /// \brief Returns true if a service of type @p serviceType has been registered. This method does ignores
    /// service initialization state.
    virtual bool ProvidesService(const ServiceType& serviceType) = 0;

    /// \brief Returns true if a service of type @p serviceType has been registered and the service has been initialized.
    virtual bool ProvidesInitializedService(const ServiceType& serviceType) = 0;

    /// \brief Initializes all registered services and throws if one or more services fail to initialize.
    virtual void InitAllServices() = 0;
};

} /* namespace BlueDwarf */