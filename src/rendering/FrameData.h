#pragma once

#include <glm/glm.hpp>

#include "pitamem/MemoryProfile.h"

namespace glove {

/** Data structure representing the current frame state. */
struct FrameData {
Profilable()
public:
    FrameData() : EnableProfilable() {
    }

    virtual ~FrameData() {
    }

    /** The current frame's Id */
    unsigned long frameId;
    /** The current view*projection matrix */
    glm::mat4 viewProjectionMatrix;
    /** The time since the last frame update */
    double deltaTime;
    /** The current context ID */
    size_t currentContext;
};


} // namespace glove