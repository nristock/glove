#include "MouseButtonEvent.h"

namespace glove {

const AbstractEvent::EventTypeId MouseButtonEvent::eventTypeId = { 0xf4, 0x66, 0xc7, 0xbb, 0x6a, 0x14, 0x42, 0x9d, 0xa8, 0xa0, 0xb6, 0x93, 0x75, 0x9d, 0xbc, 0x40 };

MouseButtonEvent::MouseButtonEvent(MouseButton button, ButtonAction buttonAction)
        : MouseButtonEvent(button, buttonAction, false, false, false, false) {

}

MouseButtonEvent::MouseButtonEvent(MouseButton button, ButtonAction buttonAction, bool shiftDown, bool controlDown, bool altDown, bool osKeyDown)
        : button(button), action(buttonAction),
          shiftDown(shiftDown), controlDown(controlDown),
          altDown(altDown), osKeyDown(osKeyDown) {

}

MouseButtonEvent::~MouseButtonEvent() {

}

const AbstractEvent::EventTypeId& MouseButtonEvent::GetEventType() const {
    return MouseButtonEvent::eventTypeId;
}
} // namespace glove