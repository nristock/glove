#pragma once

#include <glm/glm.hpp>

#include "graph/GameObject.h"

namespace glove {

/** Abstract camera representation. */
class Camera : public GameObject {
	GLOVE_MEM_ALLOC_FUNCS("Camera")
public:
	Camera();
	/** Create the camera using specific position, look at and up vectors */
	Camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up);
	virtual ~Camera();

	/** Returns the camera's view matrix */
	glm::mat4 GetViewMatrix() const { return viewMatrix; }

private:
	/** Recalculates the camera's view matrix */
	inline void RecalculateViewMatrix();

	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;

	glm::mat4 viewMatrix;
};


} // namespace glove