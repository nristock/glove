#include "glove/events/type/MouseMoveEvent.hpp"

namespace glove {

const AbstractEvent::EventTypeId MouseMoveEvent::eventTypeId = {0x14, 0xf6, 0xa3, 0x4c, 0x8e, 0x42, 0x48, 0x4d,
                                                                0x91, 0x0f, 0x05, 0xc0, 0x1f, 0xd8, 0x24, 0x5d};

MouseMoveEvent::MouseMoveEvent(double x, double y) : x(x), y(y) {
}

MouseMoveEvent::~MouseMoveEvent() {
}

const AbstractEvent::EventTypeId& MouseMoveEvent::GetEventType() const {
    return MouseMoveEvent::eventTypeId;
}
} // namespace glove