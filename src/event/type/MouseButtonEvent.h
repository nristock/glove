#pragma once

#include "pitamem/MemoryProfile.h"
#include "event/type/KeyEvent.h"

namespace glove {

enum MouseButton {
    MBTN_1 = 0,
    MBTN_2,
    MBTN_3,
    MBTN_4,
    MBTN_5,
    MBTN_6,
    MBTN_7,
    MBTN_8 = 7,

    MBTN_LEFT = MBTN_1,
    MBTN_RIGHT = MBTN_2,
    MBTN_MIDDLE = MBTN_3,

    MB_LAST = MBTN_8
};

enum ButtonAction {
    BA_PRESS,
    BA_RELEASE
};

class MouseButtonEvent {
Profilable()
public:
    MouseButtonEvent(MouseButton button, ButtonAction buttonAction);

    MouseButtonEvent(MouseButton button, ButtonAction buttonAction, bool shiftDown, bool controlDown, bool altDown, bool osKeyDown);

    virtual ~MouseButtonEvent();

    MouseButton button;
    ButtonAction action;
    bool shiftDown;
    bool controlDown;
    bool altDown;
    bool osKeyDown;
};


} // namespace glove