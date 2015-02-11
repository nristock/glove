#pragma once

#include "glove/graph/Graph.hpp"

namespace glove {
namespace ComponentFactories {

/// @ingroup RenderSubsystemInterface
class CameraComponentFactory {
public:
    static CameraBaseHandle CreateOrthographicCamera(float orthoSize, float aspectRatio);
};
}
}