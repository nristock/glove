#include <glm/gtc/matrix_transform.hpp>

#include "glove/world/Transform.hpp"

namespace BlueDwarf {

const Transform Transform::Identity;

void Transform::UpdateCache() const {
    if (!isCacheDirty) {
        return;
    }

    cachedMatrix = glm::mat4_cast(rotation);
    cachedMatrix = glm::scale(cachedMatrix, scale);
    cachedMatrix = glm::translate(cachedMatrix, position);

    isCacheDirty = false;
}

} // namespace BlueDwarf