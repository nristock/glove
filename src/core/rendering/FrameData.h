#pragma once

#include <glm/glm.hpp>

namespace glove {

/// @brief Data structure representing the current frame state.
/// @ingroup RenderSubsystemInterface
struct FrameData {
  public:
    FrameData() : frameId(0), viewProjectionMatrix(glm::mat4()), deltaTime(0) {}

    virtual ~FrameData() {}

    /// @brief The current frame's Id
    ///
    /// The frame ID is incremented with every buffer swap.
    unsigned long frameId;

    /// @brief The current view*projection matrix.
    ///
    /// It is the renderer's responsibility to set this member before actually rendering an object.
    glm::mat4 viewProjectionMatrix;

    /// @brief Seconds passed since the last frame update
    double deltaTime;
};

} // namespace glove