#include "CameraComponentFactory.h"

#include "rendering/gamecomponent/OrthoCamera.h"

namespace glove {
namespace ComponentFactories {


CameraBaseHandle CameraComponentFactory::CreateOrthographicCamera(float orthoSize, float aspectRatio) {
    return std::make_shared<glove::GameComponents::OrthoCamera>(orthoSize, aspectRatio);
}
}
}