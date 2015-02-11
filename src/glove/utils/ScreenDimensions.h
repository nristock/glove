#pragma once

#include "glove/GloveFwd.hpp"

#include <glm/glm.hpp>

namespace glove {

class ScreenDimensions {
public:
    ScreenDimensions(float width, float height);
    explicit ScreenDimensions(const glm::vec2& other);

    operator glm::vec2();

    float GetWidth() const;
    float GetHeight() const;
    float GetAspectRatio() const;

private:
    float width;
    float height;
};

}