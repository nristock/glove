#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace glove {
	
Camera::Camera() : Camera(glm::vec3(0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0)) {

}

Camera::Camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up) : position(pos), lookAt(lookAt), up(up) {
	RecalculateViewMatrix();
}

Camera::~Camera() {
	
}

void Camera::RecalculateViewMatrix() {
	viewMatrix = glm::lookAt(position, lookAt, up);
}

} // namespace glove