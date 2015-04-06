#pragma once

#include "glove/GloveApi.hpp"
#include "glove/math/IntPoint.hpp"

namespace glove {
struct GLOVE_API_EXPORT IntRect {
    IntRect() = default;

    IntRect(int32 minX, int32 minY, int32 maxX, int32 maxY) : min(minX, minY), max(maxX, maxY) {}

    IntRect(IntPoint min, IntPoint max) : min(min), max(max) {}

    bool operator==(const IntRect& other) {
        return min == other.min && max == other.max;
    }

    bool operator!=(const IntRect& other) {
        return !operator==(other);
    }

    IntPoint min;
    IntPoint max;
};
} // namespace glove
