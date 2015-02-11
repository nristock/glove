#include "glove/events/type/NativeExtensionLoadedEvent.hpp"

namespace glove {
const AbstractEvent::EventTypeId NativeExtensionLoadedEvent::eventTypeId = {
    0x10, 0x05, 0xe9, 0x04, 0x7d, 0x7a, 0x47, 0x3c, 0x86, 0xff, 0xc1, 0xcf, 0x65, 0xb3, 0x70, 0xbb};

const AbstractEvent::EventTypeId& NativeExtensionLoadedEvent::GetEventType() const {
    return NativeExtensionLoadedEvent::eventTypeId;
}
}