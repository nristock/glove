#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/events/AbstractEvent.h"

namespace glove {

struct NativeExtensionsLoadedEvent : AbstractEvent {
    static const AbstractEvent::EventTypeId eventTypeId;

    virtual const EventTypeId& GetEventType() const;
};
} /* namespace glove */