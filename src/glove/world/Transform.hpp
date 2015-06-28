#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "glove/GloveApi.hpp"

namespace BlueDwarf {

/**
* Structure to manage 3D space transformations.
*
* Position and scale are represented as glm::vec3. Rotation is represented as glm::quat.
* The Transform caches a copy of it's matrix representation to speed up subsequent Transform::ToMatrix calls.
*/
struct GLOVE_API_EXPORT Transform {
    Transform() : Transform(glm::vec3(0), glm::quat(), glm::vec3(1)) {}
    Transform(glm::vec3 position) : Transform(position, glm::quat(), glm::vec3(1)) {}
    Transform(glm::vec3 position, glm::quat rotation) : Transform(position, rotation, glm::vec3(1)) {}
    Transform(glm::vec3 position, glm::vec3 scale) : Transform(position, glm::quat(), scale) {}
    Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
        : position(position), rotation(rotation), scale(scale), isCacheDirty(true) {}
    Transform(glm::quat rotation) : Transform(glm::vec3(0), rotation, glm::vec3(1)) {}

    friend bool operator==(const Transform& transform1, const Transform& transform2) {
        return (transform1.position == transform2.position) && (transform1.rotation == transform2.rotation) &&
               (transform1.scale == transform2.scale);
    }

    friend bool operator!=(const Transform& transform1, const Transform& transform2) {
        return !(transform1 == transform2);
    }

    /// Identity Transform - No translation, no rotation, scale of 1.
    static const Transform Identity;

    /**
    * Accumulates the Transform @p other to this one.
    *
    * Position is accumulated additively.
    * Rotation is accumulated multiplicatively.
    * Scale is accumulated multiplicatively.
    */
    void Accumulate(const Transform& other) {
        position += other.position;
        rotation *= other.rotation;
        scale *= other.scale;
    }

    /// Converts the transform into a 4x4 matrix.
    const glm::mat4& ToMatrix() const {
        UpdateCache();
        return cachedMatrix;
    }

    void SetPosition(const glm::vec3& position) {
        this->position = position;
        InvalidateCache();
    }


    void SetRotation(const glm::quat& rotation) {
        this->rotation = rotation;
        InvalidateCache();
    }

    void SetScale(const glm::vec3& scale) {
        this->scale = scale;
        InvalidateCache();
    }

    const glm::vec3& GetPosition() const { return position; }
    const glm::quat& GetRotation() const { return rotation; }
    const glm::vec3& GetScale() const { return scale; }

  private:
    /// Position of this Transform
    glm::vec3 position;
    /// Rotation of this Transform (applied in local space)
    glm::quat rotation;
    /// Scale of this Transform (applied in local space)
    glm::vec3 scale;

    mutable bool isCacheDirty;
    mutable glm::mat4 cachedMatrix;

    /// Recalculates the transform matrix iff isCacheDirty flag is set.
    void UpdateCache() const;

    /// Invalidates the internal matrix cache.
    void InvalidateCache() const { isCacheDirty = true; }
};

} // namespace glove