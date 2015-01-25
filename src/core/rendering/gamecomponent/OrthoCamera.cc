#include "OrthoCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace glove {
namespace GameComponents {

OrthoCamera::OrthoCamera(float orthoSize, float aspectRatio) : orthoSize(orthoSize) {
    SetAspectRatio(aspectRatio);
}

void OrthoCamera::RecalculateProjectionMatrix() {
    projectionMatrix = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio);
}

void OrthoCamera::SetOrthoSize(float newOrthoSize) {
    orthoSize = newOrthoSize;

    RecalculateProjectionMatrix();
}
}
}
