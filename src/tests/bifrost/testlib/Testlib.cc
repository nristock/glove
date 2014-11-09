#include "TestExtension.h"

#include <core/ISystemExtension.h>

extern "C" {
glove::ISystemExtension* LoadExtension() {
    return new glove::TestExtension();
}

void UnloadExtension() {

}
}