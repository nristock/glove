#pragma once

#include <core/GloveFwd.h>

#include <core/rendering/vertex/VertexAttributeType.h>

namespace glove {

class VertexAttributeUtils {
public:
    /// @brief Returns the total size of @p attributeType in bytes
    static GLOVE_INLINE std::size_t GetAttributeTypeSize(VertexAttributeType attributeType);
private:
    VertexAttributeUtils();
};

} /* namespace glove */