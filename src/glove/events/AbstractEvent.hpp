#pragma once

#include <boost/uuid/uuid.hpp>

#include "glove/GloveFwd.hpp"

namespace glove {

struct GLOVE_API_EXPORT AbstractEvent {
  public:
    typedef boost::uuids::uuid EventTypeId;

    virtual ~AbstractEvent(){};
    virtual const EventTypeId& GetEventType() const = 0;
};

} /* namespace glove */