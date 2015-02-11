#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/events/AbstractEvent.hpp"

namespace glove {

struct GLOVE_API_EXPORT NativeExtensionsLoadedEvent : AbstractEvent {
    static const AbstractEvent::EventTypeId eventTypeId;

    virtual const EventTypeId& GetEventType() const;
};
} /* namespace glove */