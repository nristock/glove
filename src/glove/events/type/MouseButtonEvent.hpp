#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/events/type/KeyEvent.hpp"

namespace glove {

enum GLOVE_API_EXPORT MouseButton {
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

enum GLOVE_API_EXPORT ButtonAction { BA_PRESS, BA_RELEASE };

struct GLOVE_API_EXPORT MouseButtonEvent : AbstractEvent {
    static const AbstractEvent::EventTypeId eventTypeId;

    MouseButtonEvent(MouseButton button, ButtonAction buttonAction);
    MouseButtonEvent(MouseButton button, ButtonAction buttonAction, bool shiftDown, bool controlDown, bool altDown,
                     bool osKeyDown);

    virtual ~MouseButtonEvent();

    virtual const EventTypeId& GetEventType() const;

    MouseButton button;
    ButtonAction action;
    bool shiftDown;
    bool controlDown;
    bool altDown;
    bool osKeyDown;
};

} // namespace glove