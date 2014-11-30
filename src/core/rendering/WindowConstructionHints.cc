#include "WindowConstructionHints.h"

namespace glove {
WindowConstructionHints::WindowConstructionHints(const ScreenPoint& position, const ScreenDimensions& size,
                                                 const std::string& title)
    : position(position), size(size), title(title) {}

int WindowConstructionHints::GetWidth() const {
    return size.x;
}

int WindowConstructionHints::GetHeight() const {
    return size.y;
}

int WindowConstructionHints::GetPositionX() const {
    return position.x;
}

int WindowConstructionHints::GetPositionY() const {
    return position.y;
}

const std::string WindowConstructionHints::GetTitle() const {
    return title;
}
}