#pragma once

#include <glm/glm.hpp>

#include <core/graph/GameObject.h>

namespace glove {

/** Abstract camera representation. */
class Camera : public GameObject {
    Profilable()
  public:
    Camera();

    /** Create the camera using specific position, look at and up vectors */
    Camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up);
    virtual ~Camera();

    /** Returns the camera's view matrix */
    GLOVE_INLINE glm::mat4 GetViewMatrix() const;

  private:
    /** Recalculates the camera's view matrix */
    GLOVE_INLINE void RecalculateViewMatrix();

    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 up;

    glm::mat4 viewMatrix;
};

} // namespace glove