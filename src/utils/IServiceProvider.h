#pragma once

#include "core/GloveException.h"

namespace glove {

/**
 * Service provider interface template
 * The service can either be set during construction or using the SetService method.
 * If a service consumer queries the provider which doesn't have a service set an exception will be thrown.
 *
 * Be aware that the services of type T is stored as type T internally. This will trigger T's default constructor if T
 * is a non-pointer type. It is recommended to use std::shared_ptr<T> as the template parameter.
 */
template<typename T>
class IServiceProvider {
public:
    IServiceProvider() : serviceSet(false) {}
    IServiceProvider(const T& service) : serviceSet(true), service(service) {}
    virtual ~IServiceProvider() {}

    /**
     * Returns the set service or raises an exception if the server hasn't been set.
     *
     * @return The service
     * @throws GloveException if no service has been set
     */
    const T& GetService() const {
        if(serviceSet) {
            return service;
        } else {
            throw GLOVE_EXCEPTION("Service has not been set");
        }
    }

    /**
     * Returns whether the service is available (meaning the service has been set either during construction or using
     * SetService)
     */
    bool IsServiceAvailable() const { return serviceSet; }

protected:
    /** Sets the service */
    void SetService(const T& service) { this->service = service; serviceSet = true; }

private:
    bool serviceSet;
    T service;
};

} // namespace glove