#include <boost/format.hpp>

#include "glove/input/InputManager.hpp"

namespace glove {

ServiceType InputManager::serviceType = {0xb5, 0xf3, 0x62, 0x7d, 0xec, 0x2e, 0x45, 0x25, 0xaf, 0x63, 0xe6, 0x23, 0x89, 0x7f, 0x82, 0x7b};

InputManager::InputManager(EventBusPtr &eventBus) : BasicService(serviceType), mousePosition(0, 0) {

    for (int i = 0; i < KC_LAST; i++) {
        keyMap[i] = KS_UP;
    }

    for (int i = 0; i < MB_LAST; i++) {
        mouseButtonMap[i] = BS_UP;
    }

    eventBus->Subscribe<KeyEvent>(KeyEvent::eventTypeId, [this](const KeyEvent &evnt) {
        this->OnKeyEvent(evnt);
    });
    eventBus->Subscribe<MouseButtonEvent>(MouseButtonEvent::eventTypeId,
            [this](const MouseButtonEvent &evnt) {
                this->OnMouseButtonEvent(evnt);
            });
    eventBus->Subscribe<MouseMoveEvent>(MouseMoveEvent::eventTypeId,
            [this](const MouseMoveEvent &evnt) {
                this->OnMouseMoveEvent(evnt);
            });
}

InputManager::~InputManager() {
}

void InputManager::OnKeyEvent(const KeyEvent &evnt) {
    if (evnt.keyCode >= KC_LAST) {
        LOG(logger, error, (boost::format("KeyCode %1% of event is out of %2% range") % evnt.keyCode % KC_LAST).str());
        return;
    }

    KeyState previousState = keyMap[evnt.keyCode];

    if (previousState == KS_UP && evnt.action == KA_PRESS) {
        keyMap[evnt.keyCode] = KS_PRESSED;
        return;
    }

    if (previousState == KS_DOWN && evnt.action == KA_RELEASE) {
        keyMap[evnt.keyCode] = KS_RELEASED;
        return;
    }

    if (evnt.action == KA_PRESS) {
        keyMap[evnt.keyCode] = KS_DOWN;
        return;
    }

    if (evnt.action == KA_RELEASE) {
        keyMap[evnt.keyCode] = KS_UP;
        return;
    }
}

void InputManager::OnMouseButtonEvent(const MouseButtonEvent &evnt) {
    if (evnt.button >= MB_LAST) {
        LOG(logger, error,
                (boost::format("MouseButton code %1% of event is out of %2% range") % evnt.button % MB_LAST).str());
        return;
    }

    ButtonState previousState = mouseButtonMap[evnt.button];

    if (previousState == BS_UP && evnt.action == BA_PRESS) {
        mouseButtonMap[evnt.button] = BS_PRESSED;
        return;
    }

    if (previousState == BS_DOWN && evnt.action == BA_RELEASE) {
        mouseButtonMap[evnt.button] = BS_RELEASED;
        return;
    }

    if (evnt.action == BA_PRESS) {
        mouseButtonMap[evnt.button] = BS_DOWN;
        return;
    }

    if (evnt.action == BA_RELEASE) {
        mouseButtonMap[evnt.button] = BS_UP;
        return;
    }
}

void InputManager::OnMouseMoveEvent(const MouseMoveEvent &evnt) {
    mousePosition.x = evnt.x;
    mousePosition.y = evnt.y;
}

void InputManager::SyncUpdate() {
    for (int i = 0; i < KC_LAST; i++) {
        if (keyMap[i] == KS_PRESSED) {
            keyMap[i] = KS_DOWN;
        } else if (keyMap[i] == KS_RELEASED) {
            keyMap[i] = KS_UP;
        }
    }

    for (int i = 0; i < MB_LAST; i++) {
        if (mouseButtonMap[i] == BS_PRESSED) {
            mouseButtonMap[i] = BS_DOWN;
        } else if (mouseButtonMap[i] == BS_RELEASED) {
            mouseButtonMap[i] = BS_UP;
        }
    }
}

} // namespace glove