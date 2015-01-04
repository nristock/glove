#include "Dimensions.h"

namespace glove {
Dimensions::Dimensions(float width, float height) : width(width), height(height) {
}

Dimensions::Dimensions(const glm::vec2& other) : width(other.x), height(other.y) {
}

float Dimensions::GetWidth() const {
    return width;
}

float Dimensions::GetHeight() const {
    return height;
}

float Dimensions::GetAspectRatio() const {
    return width / height;
}

Dimensions::operator glm::vec2() {
    return glm::vec2(width, height);
}
}