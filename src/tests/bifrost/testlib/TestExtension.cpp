#include "TestExtension.h"
#include "TestExtensionUuid.h"

namespace glove {

void TestExtension::RegisterSubsystems(const GloveCorePtr& engineCore) {

}

const ExtensionUuid TestExtension::GetExtensionUuid() const {
    return TEST_EXTENSION_UUID;
}

const std::string& TestExtension::GetExtensionName() const {
    static const std::string extensionName = TEST_EXTENSION_NAME;
    return extensionName;
}

TestExtension::~TestExtension() {

}
}