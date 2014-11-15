#pragma once

#include <core/events/AbstractEvent.h>

namespace glove {

struct PreExtensionLoadEvent : AbstractEvent {
    static const AbstractEvent::EventTypeId eventTypeId;

    virtual GLOVE_INLINE const EventTypeId& GetEventType() const;
};
} /* namespace glove */