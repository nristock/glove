#include "CameraComponentFactory.h"

#include "graph/gamecomponent/OrthoCamera.h"

namespace glove {
namespace ComponentFactories {


SharedGameComponentHandle CameraComponentFactory::CreateOrthographicCamera(float orthoSize, float aspectRatio) {
    return std::make_shared<glove::GameComponents::OrthoCamera>(orthoSize, aspectRatio);
}
}
}