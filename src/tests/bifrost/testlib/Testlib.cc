#include "TestExtension.h"

#include <core/natex/ISystemExtension.h>

extern "C" {
glove::ISystemExtension* LoadExtension() {
    return new glove::TestExtension();
}

void UnloadExtension() {

}
}