#pragma once

#include <memory>
template <class T> using Handle = std::shared_ptr<T>;

#include <boost/uuid/uuid.hpp>

namespace glove {

class Service;
using ServiceHandle = Handle<Service>;

class ServiceRegistry;
using ServiceRegistryHandle = Handle<ServiceRegistry>;

using ServiceType = boost::uuids::uuid;
}

#if !defined(GLOVE_SERVICES_FWD_ONLY)
#include "glove/services/Service.hpp"
#include "glove/services/ServiceRegistry.hpp"
#include "glove/services/BasicService.hpp"
#include "glove/services/exceptions/ServiceNotFound.hpp"
#include "glove/services/exceptions/ServiceNotInitialized.hpp"
#endif