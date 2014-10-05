#ifndef EVENT_EVENTBUS_H_
#define EVENT_EVENTBUS_H_

#include <list>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

class EventBus : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("EventBus")
public:
	typedef std::list<EventSubscriberPtr> EventSubscriberList;

	EventBus();
	virtual ~EventBus();

	void Subscribe(EventSubscriberPtr subscriber);

	template<class EventType> void Publish(const EventType& evnt);

private:
	EventSubscriberList subscribers;
};


} // namespace glove

#endif