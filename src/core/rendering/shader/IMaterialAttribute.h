#pragma once

#include <glm/glm.hpp>

namespace glove {

/// @brief Represents a mutable attribute bound to a material.
/// @ingroup RenderSubsystemInterface
class IMaterialAttribute {
  public:
    virtual ~IMaterialAttribute() = default;

    virtual void Set(glm::mat3& value) = 0;
    virtual void Set(glm::mat4& value) = 0;
    virtual void Set(glm::vec3& value) = 0;
    virtual void Set(glm::vec4& value) = 0;
    virtual void Set(float& value) = 0;
};
}