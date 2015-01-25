#pragma once

#include "graph/Graph.h"

namespace glove {
namespace ComponentFactories {

/// @ingroup RenderSubsystemInterface
class CameraComponentFactory {
public:
    static CameraBaseHandle CreateOrthographicCamera(float orthoSize, float aspectRatio);
};
}
}