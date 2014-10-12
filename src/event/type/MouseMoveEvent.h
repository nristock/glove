#pragma once

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