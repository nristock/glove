#include "glove/rendering/gamecomponent/factories/CameraComponentFactory.hpp"
#include "glove/rendering/gamecomponent/OrthoCamera.hpp"

namespace glove {
namespace ComponentFactories {


CameraBaseHandle CameraComponentFactory::CreateOrthographicCamera(float orthoSize, float aspectRatio) {
    return std::make_shared<glove::GameComponents::OrthoCamera>(orthoSize, aspectRatio);
}
}
}