#include "EventBus.h"

#include "event/EventSubscriber.h"
#include "event/type/KeyEvent.h"
#include "event/type/MouseButtonEvent.h"
#include "event/type/MouseMoveEvent.h"

#include <algorithm>


namespace glove {

EventBus::EventBus() :
	EnableProfilable() {

}

EventBus::~EventBus() {

}

void EventBus::Subscribe(EventSubscriberPtr subscriber) {
    if (std::find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()) {
        subscribers.push_back(subscriber);
    }
}

template<>
void EventBus::Publish<KeyEvent>(const KeyEvent& evnt) {
    for (auto subscriber : subscribers) {
        subscriber->OnKeyEvent(evnt);
    }
}

template<>
void EventBus::Publish<MouseButtonEvent>(const MouseButtonEvent& evnt) {
    for (auto subscriber : subscribers) {
        subscriber->OnMouseButtonEvent(evnt);
    }
}

template<>
void EventBus::Publish<MouseMoveEvent>(const MouseMoveEvent& evnt) {
    for (auto subscriber : subscribers) {
        subscriber->OnMouseMoveEvent(evnt);
    }
}

} // namespace glove