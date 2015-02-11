#pragma once

#include <glm/glm.hpp>

#include "glove/GloveFwd.hpp"
#include "glove/graph/gamecomponent/GameComponent.h"

namespace glove {
namespace GameComponents {

/// @ingroup RenderSubsystemInterface
class CameraBase : public GameComponent {
public:
    CameraBase() = default;
    virtual ~CameraBase() = default;

    virtual void OnAttach(const GameObjectHandle& owner);

    virtual void SetAspectRatio(float aspectRatio);
    virtual const glm::mat4 GetViewProjectionMatrix();

protected:
    virtual void RecalculateViewMatrix();
    virtual void RecalculateProjectionMatrix() = 0;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    float aspectRatio = 1;

private:
    glm::mat4 prevTransformMatrix;
};

}
}