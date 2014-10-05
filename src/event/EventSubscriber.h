#ifndef EVENT_EVENTSUBSCRIBER_H_
#define EVENT_EVENTSUBSCRIBER_H_

#include "memory/GloveMemory.h"

#include "event/type/KeyEvent.h"

namespace glove {

class EventSubscriber {
	GLOVE_MEM_ALLOC_FUNCS("EventSubscriber")
public:
	EventSubscriber();
	virtual ~EventSubscriber();

	virtual void OnKeyEvent(const KeyEvent& evnt) {};
};


} // namespace glove

#endif