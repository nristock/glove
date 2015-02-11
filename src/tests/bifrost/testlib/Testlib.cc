#include <glove/natex/Natex.hpp>

#include "TestExtension.hpp"

extern "C" {
glove::ISystemExtensionPtr LoadExtension() {
    return glove::ISystemExtensionPtr(new glove::TestExtension(), [=](glove::TestExtension* ptr) {delete ptr;});
}

void UnloadExtension() {

}
}