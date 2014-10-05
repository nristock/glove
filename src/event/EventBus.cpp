#include "EventBus.h"

#include "event/EventSubscriber.h"
#include "event/type/KeyEvent.h"


namespace glove {
	
EventBus::EventBus() {

}

EventBus::~EventBus() {
	
}

void EventBus::Subscribe(EventSubscriberPtr subscriber) {
	if (std::find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()) {
		subscribers.push_back(subscriber);
	}
}

template<> void EventBus::Publish<KeyEvent>(const KeyEvent& evnt) {
	for (auto subscriber : subscribers) {
		subscriber->OnKeyEvent(evnt);
	}
}

} // namespace glove