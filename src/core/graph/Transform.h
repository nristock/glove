#pragma once

#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace glove {

/**
* Structure to manage 3D space transformations.
* Position and scale are represented as glm::vec3. Rotation is represented as glm::quat.
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
    * Invokes Transform::RecalculateMatrix(bool notifyModify) with notifyModify=true.
    */
    void RecalculateMatrix();

    /**
    * Recalculates local transformation matrix and invokes the registered onModify callback if it has been set.
    * @param [in] notifyModify If true the registered onModify callback will be invoked.
    */
    void RecalculateMatrix(bool notifyModify);

    /**
    * Recalculates the accumulated transformation matrix using the specified parent.
    * @param [in] parent The parent transform.
    */
    void RecalculateAccumulatedTransform(const Transform& parent);

    /**
    * Recalculates the local transform matrix if isDirty has been set and returns the 4x4 matrix.
    * @return localTransform
    */
    glm::mat4 GetLocalTransform() {
        if (isDirty) RecalculateMatrix();
        return localTransform;
    }

    /**
    * Returns the accumulated tranform matrix (parent's accumulated matrix * localTransform)
    * @return globalTransform
    */
    glm::mat4 GetGlobalTransform() const {
        return globalTransform;
    }

    /**
    * Calls Transform::SetPosition(const glm::vec3&, bool updateMatrix) with updateMatrix=true.
    */
    void SetPosition(const glm::vec3& position);

    /**
    * Calls Transform::SetRotation(const glm::quat&, bool updateMatrix) with updateMatrix=true.
    */
    void SetRotation(const glm::quat& rotation);

    /**
    * Calls Transform::SetScale(const glm::vec3&, bool updateMatrix) with updateMatrix=true.
    */
    void SetScale(const glm::vec3& scale);

    /**
    * Sets the Transform's position and updates the local transform matrix if requested.
    * @param [in] position The new position
    * @param [in] updateMatrix Specifies wether the local matrix should be updated immediately (true) or if the isDirty flag should be set (false).
    */
    void SetPosition(const glm::vec3& position, bool updateMatrix);

    /**
    * Sets the Transform's rotation and updates the local transform matrix if requested.
    * @param [in] position The new rotation
    * @param [in] updateMatrix Specifies wether the local matrix should be updated immediately (true) or if the isDirty flag should be set (false).
    */
    void SetRotation(const glm::quat& rotation, bool updateMatrix);

    /**
    * Sets the Transform's scale and updates the local transform matrix if requested.
    * @param [in] position The new scale
    * @param [in] updateMatrix Specifies wether the local matrix should be updated immediately (true) or if the isDirty flag should be set (false).
    */
    void SetScale(const glm::vec3& scale, bool updateMatrix);

    const glm::vec3& GetPosition() const {
        return position;
    }

    const glm::quat& GetRotation() const {
        return rotation;
    }

    const glm::vec3& GetScale() const {
        return scale;
    }

    /**
    * Sets an onModify callback.
    */
    void SetModifyCallback(std::function<void()> callback);

private:
    bool isDirty;
    bool isGlobalDirty;

    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    glm::mat4 localTransform;
    glm::mat4 globalTransform;

    std::function<void()> onModify;
};


} // namespace glove