#include "Transform.h"

namespace glove {
	
Transform::Transform() : Transform(glm::vec3(0), glm::quat(), glm::vec3(1)) {

}

Transform::Transform(glm::vec3 position) : Transform(position, glm::quat(), glm::vec3(1)) {

}

Transform::Transform(glm::vec3 position, glm::quat rotation) : Transform(position, rotation, glm::vec3(1)) {

}

Transform::Transform(glm::vec3 position, glm::vec3 scale) : Transform(position, glm::quat(), scale) {

}

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale) : position(position), rotation(rotation), scale(scale) {

}

Transform::Transform(glm::quat rotation) : Transform(glm::vec3(0), rotation, glm::vec3(1)) {

}

} // namespace glove