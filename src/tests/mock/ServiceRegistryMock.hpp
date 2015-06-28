#include <gmock/gmock.hpp>

#include <glove/services/ServiceRegistry.hpp>
#include <glove/services/Services.hpp>

namespace BlueDwarf {
class ServiceRegistryMock : public ServiceRegistry {
  public:
    MOCK_METHOD1(RegisterService, void(const ServiceHandle& service));
    MOCK_METHOD1(FindService, ServiceHandle(const ServiceType& serviceType));
    MOCK_METHOD1(GetService, ServiceHandle(const ServiceType& serviceType));
    MOCK_METHOD1(ProvidesService, bool(const ServiceType& serviceType));
    MOCK_METHOD1(ProvidesInitializedService, bool(const ServiceType& serviceType));
    MOCK_METHOD0(InitAllServices, void());
};
}