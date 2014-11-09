#pragma once

#include <boost/uuid/uuid.hpp>

#include <core/GloveFwd.h>

namespace glove {

struct AbstractEvent {
public:
    typedef boost::uuids::uuid EventTypeId;

    virtual ~AbstractEvent() {};
    virtual GLOVE_INLINE const EventTypeId& GetEventType() const = 0;

};

} /* namespace glove */