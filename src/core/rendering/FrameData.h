#pragma once

#include <glm/glm.hpp>

#include <core/pitamem/MemoryProfile.h>

namespace glove {

/** Data structure representing the current frame state. */
struct FrameData {
    Profilable()
  public:
    FrameData() : EnableProfilable(), frameId(0), viewProjectionMatrix(glm::mat4()), deltaTime(0), currentContext(0) {}

    virtual ~FrameData() {}

    /** The current frame's Id */
    unsigned long frameId;
    /** The current view*projection matrix */
    glm::mat4 viewProjectionMatrix;
    /** The time since the last frame update */
    double deltaTime;
    /** The current context ID */
    std::size_t currentContext;
};

} // namespace glove