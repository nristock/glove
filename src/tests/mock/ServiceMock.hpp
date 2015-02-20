#include <gmock/gmock.hpp>

#include <glove/services/Services.hpp>

namespace glove {
class ServiceMock : public Service {
  public:
    MOCK_METHOD1(Init, bool(ServiceRegistry& serviceRegistry));
    MOCK_METHOD0(GetType, ServiceType());
};
}