#include <glm/gtc/matrix_transform.hpp>

#include "glove/graph/Transform.hpp"

namespace glove {

Transform::Transform() : Transform(glm::vec3(0), glm::quat(), glm::vec3(1)) {
}

Transform::Transform(glm::vec3 position) : Transform(position, glm::quat(), glm::vec3(1)) {
}

Transform::Transform(glm::vec3 position, glm::quat rotation) : Transform(position, rotation, glm::vec3(1)) {
}

Transform::Transform(glm::vec3 position, glm::vec3 scale) : Transform(position, glm::quat(), scale) {
}

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale) {
    RecalculateMatrix();
    globalTransform = localTransform;
}

Transform::Transform(glm::quat rotation) : Transform(glm::vec3(0), rotation, glm::vec3(1)) {
}

const Transform& Transform::Identity() {
    static const Transform identity;

    return identity;
}

void Transform::RecalculateMatrix() {
    localTransform = glm::mat4_cast(rotation);
    localTransform = glm::scale(localTransform, scale);
    localTransform = glm::translate(localTransform, position);
}

void Transform::RecalculateAccumulatedTransform(const Transform& parent) {
    globalTransform = parent.GetGlobalTransform() * GetLocalTransform();
}

void Transform::SetPosition(const glm::vec3& position) {
    this->position = position;

    RecalculateMatrix();
}

void Transform::SetRotation(const glm::quat& rotation) {
    this->rotation = rotation;

    RecalculateMatrix();
}

void Transform::SetScale(const glm::vec3& scale) {
    this->scale = scale;

    RecalculateMatrix();
}

const glm::mat4& Transform::GetLocalTransform() {
    return localTransform;
}

bool operator==(const Transform& transform1, const Transform& transform2) {
    return (transform1.position == transform2.position) && (transform1.rotation == transform2.rotation) &&
           (transform1.scale == transform2.scale);
}

bool operator!=(const Transform& transform1, const Transform& transform2) {
    return !(transform1 == transform2);
}
} // namespace glove