#pragma once

#include <map>
#include <functional>

#include "glove/GloveFwd.hpp"
#include "glove/events/AbstractEvent.h"

namespace glove {

/** Class implementing a simple sync Publish-Subscribe event bus */
class EventBus {
  public:
    typedef std::function<void(const AbstractEvent* evnt)> GenericEventHandler;
    typedef std::multimap<AbstractEvent::EventTypeId, GenericEventHandler> EventSubscriberList;
    typedef EventSubscriberList::iterator EventSubscriberListIterator;

    EventBus();
    virtual ~EventBus();

    template <typename EventType>
    void Subscribe(const AbstractEvent::EventTypeId& eventType, std::function<void(const EventType&)> callback) {
        subscribers.insert(std::make_pair(eventType, [=](const AbstractEvent* evnt) {
            const EventType& typedEvent = *static_cast<const EventType*>(evnt);
            callback(typedEvent);
        }));
    }

    template <class EventType> void Publish(const EventType& evnt) {
        const AbstractEvent* abstractEvent = static_cast<const AbstractEvent*>(&evnt);
        std::pair<EventSubscriberListIterator, EventSubscriberListIterator> range =
            subscribers.equal_range(abstractEvent->GetEventType());

        for (EventSubscriberListIterator iter = range.first; iter != range.second; ++iter) {
            iter->second(abstractEvent);
        }
    }

  private:
    EventSubscriberList subscribers;
};

} // namespace glove