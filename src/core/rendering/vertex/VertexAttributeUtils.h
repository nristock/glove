#pragma once

#include <core/GloveFwd.h>

#include <core/rendering/vertex/VertexAttributeType.h>

namespace glove {

/// @ingroup RenderSubsystemInterface
template <VertexAttributeType T> struct VertexAttributeUtils {
    /// @brief Returns the total size of T in byte.
    static GLOVE_INLINE std::size_t GetTypeSize();
    /// @brief Returns the number of components in T. (e.g. FLOAT3 has 3 float components)
    static GLOVE_INLINE std::size_t GetComponentCount();

    VertexAttributeUtils() = delete;
};

} /* namespace glove */