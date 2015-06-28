#include "glove/utils/ScreenDimensions.hpp"

namespace BlueDwarf {
ScreenDimensions::ScreenDimensions(float width, float height) : width(width), height(height) {
}

ScreenDimensions::ScreenDimensions(const glm::vec2& other) : width(other.x), height(other.y) {
}

float ScreenDimensions::GetWidth() const {
    return width;
}

float ScreenDimensions::GetHeight() const {
    return height;
}

float ScreenDimensions::GetAspectRatio() const {
    return width / height;
}

ScreenDimensions::operator glm::vec2() {
    return glm::vec2(width, height);
}
}