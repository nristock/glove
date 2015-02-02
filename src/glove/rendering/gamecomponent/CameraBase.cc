#include "CameraBase.h"

#include "glove/graph/gameobject/GameObject.h"

namespace glove {
namespace GameComponents {

void CameraBase::OnAttach(const GameObjectHandle& owner) {
    GameComponent::OnAttach(owner);

    RecalculateViewMatrix();
}

void CameraBase::RecalculateViewMatrix() {
    const GameObjectHandle ownerHandle = this->owner.lock();
    if(prevTransformMatrix == ownerHandle->GetTransform().GetGlobalTransform()) {
        // location/rotation didn't change so we don't have to recalculate
        return;
    }

    prevTransformMatrix = ownerHandle->GetTransform().GetGlobalTransform();
    viewMatrix = glm::inverse(prevTransformMatrix);
}

const glm::mat4 CameraBase::GetViewProjectionMatrix() {
    RecalculateViewMatrix();

    return viewMatrix * projectionMatrix;
}

void CameraBase::SetAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;

    RecalculateProjectionMatrix();
}
}
}