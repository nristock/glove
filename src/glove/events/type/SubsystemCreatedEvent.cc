#include "glove/events/type/SubsystemCreatedEvent.hpp"

namespace glove {
const AbstractEvent::EventTypeId SubsystemCreatedEvent::eventTypeId = {0x5f, 0x32, 0xd6, 0x73, 0x23, 0x38, 0x43, 0x42,
                                                                       0xab, 0x94, 0x8c, 0xf5, 0x6b, 0xdf, 0x54, 0x7e};

const AbstractEvent::EventTypeId& SubsystemCreatedEvent::GetEventType() const {
    return SubsystemCreatedEvent::eventTypeId;
}
}