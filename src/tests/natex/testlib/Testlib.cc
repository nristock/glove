#include <glove/natex/Natex.hpp>

extern "C" {
int TestLibFunction(int param) {
    return param;
}
//
//BlueDwarf::ISystemExtensionPtr LoadExtension() {
//    return BlueDwarf::ISystemExtensionPtr();
//}

void UnloadExtension() {
}
}