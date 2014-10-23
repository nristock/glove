#include "MouseButtonEvent.h"

namespace glove {

MouseButtonEvent::MouseButtonEvent(MouseButton button, ButtonAction buttonAction)
        : MouseButtonEvent(button, buttonAction, false, false, false, false) {

}

MouseButtonEvent::MouseButtonEvent(MouseButton button, ButtonAction buttonAction, bool shiftDown, bool controlDown, bool altDown, bool osKeyDown)
        : button(button), action(buttonAction),
          shiftDown(shiftDown), controlDown(controlDown),
          altDown(altDown), osKeyDown(osKeyDown), EnableProfilable() {

}

MouseButtonEvent::~MouseButtonEvent() {

}

} // namespace glove