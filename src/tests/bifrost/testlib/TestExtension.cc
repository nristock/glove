#include "TestExtension.hpp"
#include "TestExtensionUuid.hpp"

namespace glove {

void TestExtension::RegisterSubsystems(const GloveCorePtr& engineCore) {

}

const ExtensionUuid TestExtension::GetExtensionUuid() const {
    return TEST_MODULE_NAME;
}

const std::string& TestExtension::GetExtensionName() const {
    static const std::string extensionName = TEST_EXTENSION_NAME;
    return extensionName;
}

TestExtension::~TestExtension() {

}

void TestExtension::RegisterSubsystems(const ISubsystemDefinitionRegistryPtr& subsystemRegistry) {

}
}