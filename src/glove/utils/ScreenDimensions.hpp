#pragma once

#include <glm/glm.hpp>

#include "glove/GloveApi.hpp"

namespace glove {

class GLOVE_API_EXPORT ScreenDimensions {
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