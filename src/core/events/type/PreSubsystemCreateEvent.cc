#include "PreSubsystemCreateEvent.h"

namespace glove {
const AbstractEvent::EventTypeId PreSubsystemCreateEvent::eventTypeId = {
    0x66, 0xea, 0x90, 0xe0, 0xef, 0xfd, 0x41, 0xc7, 0xa2, 0x05, 0x84, 0xcb, 0xb6, 0xe5, 0x43, 0x07};

const AbstractEvent::EventTypeId& PreSubsystemCreateEvent::GetEventType() const {
    return PreSubsystemCreateEvent::eventTypeId;
}
}