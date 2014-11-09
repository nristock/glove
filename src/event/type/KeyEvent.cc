#include "KeyEvent.h"

namespace glove {

const AbstractEvent::EventTypeId KeyEvent::eventTypeId = { 0x84, 0x87, 0xe1, 0xe9, 0xfa, 0xbd, 0x4b, 0xf5, 0x9f, 0x89, 0x9d, 0x85, 0xb1, 0xf6, 0xad, 0xd6 };

KeyEvent::KeyEvent(KeyCode keyCode, KeyAction action) : KeyEvent(keyCode, action, false, false, false, false) {

}

KeyEvent::KeyEvent(KeyCode keyCode, KeyAction action, bool shiftDown, bool controlDown, bool altDown, bool osKeyDown)
        : keyCode(keyCode), action(action),
          shiftDown(shiftDown), controlDown(controlDown),
          altDown(altDown), osKeyDown(osKeyDown) {

}

KeyEvent::~KeyEvent() {

}

const AbstractEvent::EventTypeId& KeyEvent::GetEventType() const {
    return KeyEvent::eventTypeId;
}
} // namespace glove