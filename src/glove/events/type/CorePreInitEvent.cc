#include "glove/events/type/CorePreInitEvent.hpp"

namespace glove {
const AbstractEvent::EventTypeId CorePreInitEvent::eventTypeId = {0x1c, 0x23, 0x4f, 0x26, 0xaf, 0x21, 0x47, 0x1f,
                                                                  0xbe, 0x8c, 0x12, 0x97, 0x54, 0xbf, 0x37, 0xbc};

const AbstractEvent::EventTypeId& CorePreInitEvent::GetEventType() const {
    return CorePreInitEvent::eventTypeId;
}
}