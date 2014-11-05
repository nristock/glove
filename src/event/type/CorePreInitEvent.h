#pragma once

#include <event/AbstractEvent.h>

namespace glove {

struct CorePreInitEvent : AbstractEvent {
    static const AbstractEvent::EventTypeId eventTypeId;

    virtual const EventTypeId& GetEventType() const;
};
} /* namespace glove */