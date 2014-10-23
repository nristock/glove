#pragma once

#include <list>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

/** Class implementing a simple sync Publish-Subscribe event bus */
class EventBus : public GloveObject {
Profilable()
public:
    typedef std::list<EventSubscriberPtr> EventSubscriberList;

    EventBus();

    virtual ~EventBus();

    void Subscribe(EventSubscriberPtr subscriber);

    template<class EventType>
    void Publish(const EventType& evnt);

private:
    EventSubscriberList subscribers;
};


} // namespace glove