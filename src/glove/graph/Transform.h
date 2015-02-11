#pragma once

#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "glove/GloveFwd.hpp"

namespace glove {

/**
* Structure to manage 3D space transformations.
* Position and scale are represented as glm::vec3. Rotation is represented as glm::quat.
* TODO: Implement defered update
*/
struct Transform {
    Transform();
    Transform(glm::vec3 position);
    Transform(glm::vec3 position, glm::quat rotation);
    Transform(glm::vec3 position, glm::vec3 scale);
    Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
    Transform(glm::quat rotation);

    friend bool operator==(const Transform& transform1, const Transform& transform2);
    friend bool operator!=(const Transform& transform1, const Transform& transform2);

    /**
    * Identity transform - No translation, no rotation, scale of 1.
    */
    static const Transform& Identity();

    /**
    * Recalculates the accumulated transformation matrix using the specified parent.
    * @param [in] parent The parent transform.
    */
    void RecalculateAccumulatedTransform(const Transform& parent);

    /**
    * Recalculates the local transform matrix if isDirty has been set and returns the 4x4 matrix.
    * @return localTransform
    */
    const glm::mat4& GetLocalTransform();

    /**
    * Returns the accumulated tranform matrix (parent's accumulated matrix * localTransform)
    * @return globalTransform
    */
    const glm::mat4& GetGlobalTransform() const { return globalTransform; }

    /**
    * Sets the Transform's position and updates the local transform matrix.
    * @param [in] position The new position
    */
    void SetPosition(const glm::vec3& position);

    /**
    * Sets the Transform's rotation and updates the local transform matrix.
    * @param [in] position The new rotation
    */
    void SetRotation(const glm::quat& rotation);

    /**
    * Sets the Transform's scale and updates the local transform matrix.
    * @param [in] position The new scale
    */
    void SetScale(const glm::vec3& scale);

    const glm::vec3& GetPosition() const { return position; }
    const glm::quat& GetRotation() const { return rotation; }
    const glm::vec3& GetScale() const { return scale; }

  private:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    glm::mat4 localTransform;
    glm::mat4 globalTransform;

    /**
    * Recalculates the local transform matrix using the transforms position/rotation/scale.
    */
    void RecalculateMatrix();
};

} // namespace glove