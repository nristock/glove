#pragma once

#include <core/GloveFwd.h>

#include <glm/glm.hpp>

namespace glove {

class ScreenDimensions {
public:
    ScreenDimensions(float width, float height);
    explicit ScreenDimensions(const glm::vec2& other);

    operator glm::vec2();

    GLOVE_INLINE float GetWidth() const;
    GLOVE_INLINE float GetHeight() const;
    GLOVE_INLINE float GetAspectRatio() const;

private:
    float width;
    float height;
};

}