#pragma once

#include "pitamem/MemoryProfile.h"

namespace glove {

struct MouseMoveEvent {
Profilable()
public:
    MouseMoveEvent(double x, double y);

    virtual ~MouseMoveEvent();

    double x;
    double y;
};


} // namespace glove