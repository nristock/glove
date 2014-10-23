#include "MouseMoveEvent.h"

namespace glove {

MouseMoveEvent::MouseMoveEvent(double x, double y) : x(x), y(y), EnableProfilable() {

}

MouseMoveEvent::~MouseMoveEvent() {

}

} // namespace glove