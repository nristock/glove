#include "NativeExtensionsLoadedEvent.h"

namespace glove {
const AbstractEvent::EventTypeId NativeExtensionsLoadedEvent::eventTypeId = {
    0x21, 0x2a, 0xff, 0xfa, 0xdf, 0x1b, 0x4f, 0x3a, 0x94, 0x5f, 0xc0, 0xd0, 0x40, 0xa6, 0x1d, 0x26};

const AbstractEvent::EventTypeId& NativeExtensionsLoadedEvent::GetEventType() const {
    return NativeExtensionsLoadedEvent::eventTypeId;
}
}