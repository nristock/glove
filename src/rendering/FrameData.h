#ifndef RENDERING_FRAMEDATA_H_
#define RENDERING_FRAMEDATA_H_

#include <glm/glm.hpp>

#include "memory/GloveMemory.h"

namespace glove {

struct FrameData {
	GLOVE_MEM_ALLOC_FUNCS("FrameData")
public:
	unsigned long frameId;
	glm::mat4 viewProjectionMatrix;
	double deltaTime;
};


} // namespace glove

#endif