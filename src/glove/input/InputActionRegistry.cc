#include "glove/utils/DebugUtils.hpp"
#include "glove/input/InputActionRegistry.hpp"

namespace BlueDwarf {

const ServiceType InputActionRegistry::serviceType = {0x6f, 0x4b, 0x54, 0xab, 0x3c, 0xd0, 0x41, 0xe8, 0x9e, 0x8a, 0xef, 0x00, 0xcd, 0xbd, 0xe0, 0x9b};

InputActionRegistry::InputActionRegistry() : BasicService(serviceType) {
    inputActions.reserve(256);
}

void InputActionRegistry::RegisterInputAction(InputActionHandle inputAction) {
    inputActions.push_back(std::move(inputAction));
}

void InputActionRegistry::MapActionKey(const Key& key, InputActionHandle inputAction) {
    DebugAssert(std::find(inputActions.begin(), inputActions.end(), inputAction) == inputActions.end());

    actionMappings.emplace(key.GetId(), std::move(inputAction));
}
}