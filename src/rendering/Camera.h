#ifndef RENDERING_CAMERA_H_
#define RENDERING_CAMERA_H_

#include <glm/glm.hpp>

#include "graph/GameObject.h"

namespace glove {

class Camera : public GameObject {
	GLOVE_MEM_ALLOC_FUNCS("Camera")
public:
	Camera();
	Camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up);
	virtual ~Camera();

	glm::mat4 GetViewMatrix() const { return viewMatrix; }

private:
	inline void RecalculateViewMatrix();

	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;

	glm::mat4 viewMatrix;
};


} // namespace glove

#endif