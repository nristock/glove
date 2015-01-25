#pragma once

#include <glm/glm.hpp>

#include "GloveFwd.h"
#include "graph/gamecomponent/GameComponent.h"

namespace glove {
namespace GameComponents {

/// @ingroup RenderSubsystemInterface
class CameraBase : public GameComponent {
public:
    CameraBase() = default;
    virtual ~CameraBase() = default;

    virtual void OnAttach(const GameObjectHandle& owner);

    virtual GLOVE_INLINE void SetAspectRatio(float aspectRatio);
    virtual GLOVE_INLINE const glm::mat4 GetViewProjectionMatrix();

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