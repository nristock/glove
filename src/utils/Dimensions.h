#pragma once

#include <core/GloveFwd.h>

#include <glm/glm.hpp>

namespace glove {

class Dimensions {
public:
    Dimensions(float width, float height);
    explicit Dimensions(const glm::vec2& other);

    operator glm::vec2();

    GLOVE_INLINE float GetWidth() const;
    GLOVE_INLINE float GetHeight() const;
    GLOVE_INLINE float GetAspectRatio() const;

private:
    float width;
    float height;
};

}