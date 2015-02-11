#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/events/AbstractEvent.hpp"

namespace glove {

struct GLOVE_API_EXPORT MouseMoveEvent : AbstractEvent {
    static const AbstractEvent::EventTypeId eventTypeId;

    MouseMoveEvent(double x, double y);

    virtual ~MouseMoveEvent();

    virtual const EventTypeId& GetEventType() const;

    double x;
    double y;
};

} // namespace glove