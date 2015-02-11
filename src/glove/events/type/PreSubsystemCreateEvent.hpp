#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/events/AbstractEvent.hpp"

namespace glove {

struct GLOVE_API_EXPORT PreSubsystemCreateEvent : AbstractEvent {
    static const AbstractEvent::EventTypeId eventTypeId;

    virtual const EventTypeId& GetEventType() const;
};
} /* namespace glove */