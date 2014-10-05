#ifndef EVENT_TYPE_MOUSEMOVEEVENT_H_
#define EVENT_TYPE_MOUSEMOVEEVENT_H_

#include "memory/GloveMemory.h"

namespace glove {

struct MouseMoveEvent {
	GLOVE_MEM_ALLOC_FUNCS("MouseMoveEvent")
public:
	MouseMoveEvent(double x, double y);
	virtual ~MouseMoveEvent();

	double x;
	double y;
};


} // namespace glove

#endif