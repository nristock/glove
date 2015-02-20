#pragma once

#include <map>
#include <functional>

#include "glove/GloveFwd.hpp"
#include "glove/events/AbstractEvent.hpp"
#include "glove/services/Services.hpp"

namespace glove {

/** Class implementing a simple sync Publish-Subscribe event bus */
class GLOVE_API_EXPORT EventBus : public BasicService  {
  public:
    typedef std::function<void(const char* evnt)> GenericEventHandler;
    typedef std::multimap<AbstractEvent::EventTypeId, GenericEventHandler> EventSubscriberList;
    typedef EventSubscriberList::iterator EventSubscriberListIterator;

    static ServiceType serviceType;

    EventBus();
    virtual ~EventBus();

    template <typename EventType>
    void Subscribe(const AbstractEvent::EventTypeId& eventType, std::function<void(const EventType&)> callback) {
        subscribers.insert(std::make_pair(eventType, [=](const char* evnt) {
            const EventType& typedEvent = *reinterpret_cast<const EventType*>(evnt);
            callback(typedEvent);
        }));
    }

    template <class EventType> void Publish(const EventType& evnt) {
        std::pair<EventSubscriberListIterator, EventSubscriberListIterator> range =
            subscribers.equal_range(evnt.GetEventType());

        for (EventSubscriberListIterator iter = range.first; iter != range.second; ++iter) {
            iter->second(reinterpret_cast<const char*>(&evnt));
        }
    }

  private:
    EventSubscriberList subscribers;
};

} // namespace glove