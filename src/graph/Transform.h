#ifndef GRAPH_TRANSFORM_H_
#define GRAPH_TRANSFORM_H_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "memory/GloveMemory.h"

namespace glove {

struct Transform {
	GLOVE_MEM_ALLOC_FUNCS("Transform");
public:
	Transform();
	Transform(glm::vec3 position);
	Transform(glm::vec3 position, glm::quat rotation);
	Transform(glm::vec3 position, glm::vec3 scale);

	Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

	Transform(glm::quat rotation);

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
};


} // namespace glove

#endif