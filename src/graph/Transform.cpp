#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace glove {

Transform Transform::Identity = Transform();
	
Transform::Transform() : Transform(glm::vec3(0), glm::quat(), glm::vec3(1)) {

}

Transform::Transform(glm::vec3 position) : Transform(position, glm::quat(), glm::vec3(1)) {

}

Transform::Transform(glm::vec3 position, glm::quat rotation) : Transform(position, rotation, glm::vec3(1)) {

}

Transform::Transform(glm::vec3 position, glm::vec3 scale) : Transform(position, glm::quat(), scale) {

}

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale) : position(position), rotation(rotation), scale(scale) {
	globalTransform = glm::mat4(1);
	RecalculateMatrix();
}

Transform::Transform(glm::quat rotation) : Transform(glm::vec3(0), rotation, glm::vec3(1)) {

}

void Transform::RecalculateMatrix(bool notifyModify) {
	localTransform = glm::mat4_cast(rotation);
	localTransform = glm::scale(localTransform, scale);
	localTransform = glm::translate(localTransform, position);
	isDirty = false;

	if (notifyModify && onModify) onModify();
}

void Transform::RecalculateMatrix() {
	RecalculateMatrix(true);
}

void Transform::RecalculateAccumulatedTransform(const Transform& parent) {
	globalTransform = parent.GetGlobalTransform() * GetLocalTransform();
}

void Transform::SetPosition(const glm::vec3& position, bool updateMatrix) {
	this->position = position;
	
	if (updateMatrix) RecalculateMatrix();
	else isDirty = true;
}

void Transform::SetRotation(const glm::quat& rotation, bool updateMatrix) {
	this->rotation = rotation;
	
	if (updateMatrix) RecalculateMatrix();
	else isDirty = true;
}

void Transform::SetScale(const glm::vec3& scale, bool updateMatrix) {
	this->scale = scale;
	
	if (updateMatrix) RecalculateMatrix();
	else isDirty = true;
}

void Transform::SetPosition(const glm::vec3& position) {
	SetPosition(position, true);
}

void Transform::SetRotation(const glm::quat& rotation) {
	SetRotation(rotation, true);
}

void Transform::SetScale(const glm::vec3& scale) {
	SetScale(scale, true);
}

void Transform::SetModifyCallback(std::function<void()> callback) {
	onModify = callback;
}

} // namespace glove