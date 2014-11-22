#include <core/natex/Natex.h>

extern "C" {
int TestLibFunction(int param) {return param;}

glove::ISystemExtensionPtr LoadExtension() {
    return glove::ISystemExtensionPtr();
}

void UnloadExtension() {

}
}