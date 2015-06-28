#include <gmock/gmock.hpp>

#include <glove/natex/Module.hpp>
#include <glove/services/ServiceRegistry.hpp>

namespace BlueDwarf {
    class ModuleMock : public Module {
      public:
        MOCK_METHOD0(Load, void());
        MOCK_METHOD0(Unload, void());

        MOCK_METHOD1(RegisterServices, void(ServiceRegistry& serviceRegistry));
        MOCK_CONST_METHOD0(GetName, const std::string&());
        MOCK_CONST_METHOD0(GetVersion, const ModuleVersionInfo&());
    };
}