#pragma once

#include "glove/GloveApi.hpp"
#include "glove/graph/Graph.hpp"

namespace glove {
namespace ComponentFactories {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT CameraComponentFactory {
public:
    static CameraBaseHandle CreateOrthographicCamera(float orthoSize, float aspectRatio);
};
}
}