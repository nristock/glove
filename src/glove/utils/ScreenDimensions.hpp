#pragma once

#include <glm/glm.hpp>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {

class BD_API_EXPORT ScreenDimensions {
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