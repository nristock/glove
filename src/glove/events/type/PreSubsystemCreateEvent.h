#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/events/AbstractEvent.h"

namespace glove {

struct PreSubsystemCreateEvent : AbstractEvent {
    static const AbstractEvent::EventTypeId eventTypeId;

    virtual const EventTypeId& GetEventType() const;
};
} /* namespace glove */