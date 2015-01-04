#pragma once

#include <core/graph/Graph.h>

namespace glove {
namespace ComponentFactories {

class CameraComponentFactory {
public:
    static SharedGameComponentHandle CreateOrthographicCamera(float orthoSize, float aspectRatio);
};
}
}