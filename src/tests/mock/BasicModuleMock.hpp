#include <gmock/gmock.hpp>

#include <glove/natex/BasicModule.hpp>
#include <glove/services/ServiceRegistry.hpp>

namespace glove {
class BasicModuleMock : public BasicModule {
  public:
    BasicModuleMock(const std::string& name, const ModuleVersionInfo& moduleVersionInfo) : BasicModule(name, moduleVersionInfo) {}

    MOCK_METHOD1(RegisterServices, void(ServiceRegistry& serviceRegistry));
    MOCK_METHOD0(Load, void());
    MOCK_METHOD0(Unload, void());
};
}