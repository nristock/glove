#include <gmock/gmock.hpp>

#include <glove/services/Services.hpp>

namespace BlueDwarf {
class ServiceMock : public Service {
  public:
    MOCK_METHOD0(NeedsInitialization, bool());
    MOCK_METHOD1(Init, bool(ServiceRegistry& serviceRegistry));
    MOCK_METHOD0(GetType, ServiceType());
};
}