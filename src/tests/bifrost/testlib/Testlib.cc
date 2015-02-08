#include "TestExtension.h"

#include <glove/natex/Natex.h>

extern "C" {
glove::ISystemExtensionPtr LoadExtension() {
    return glove::ISystemExtensionPtr(new glove::TestExtension(), [=](glove::TestExtension* ptr) {delete ptr;});
}

void UnloadExtension() {

}
}