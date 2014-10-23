#include "KeyEvent.h"

namespace glove {

KeyEvent::KeyEvent(KeyCode keyCode, KeyAction action) : KeyEvent(keyCode, action, false, false, false, false) {

}

KeyEvent::KeyEvent(KeyCode keyCode, KeyAction action, bool shiftDown, bool controlDown, bool altDown, bool osKeyDown)
        : keyCode(keyCode), action(action),
          shiftDown(shiftDown), controlDown(controlDown),
          altDown(altDown), osKeyDown(osKeyDown), EnableProfilable() {

}

KeyEvent::~KeyEvent() {

}

} // namespace glove