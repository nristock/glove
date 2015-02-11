#include "glove/events/type/PreExtensionLoadEvent.hpp"

namespace glove {
const AbstractEvent::EventTypeId PreExtensionLoadEvent::eventTypeId = {0x41, 0xb1, 0x65, 0x32, 0x94, 0x95, 0x47, 0xc8,
                                                                       0x83, 0x28, 0x2a, 0x9d, 0xab, 0xe1, 0xc8, 0xdc};

const AbstractEvent::EventTypeId& PreExtensionLoadEvent::GetEventType() const {
    return PreExtensionLoadEvent::eventTypeId;
}
}