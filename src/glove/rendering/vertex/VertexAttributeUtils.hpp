#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/rendering/vertex/VertexAttributeType.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
template <VertexAttributeType T> struct VertexAttributeUtils {
    /// @brief Returns the total size of T in byte.
    static std::size_t GetTypeSize();
    /// @brief Returns the number of components in T. (e.g. FLOAT3 has 3 float components)
    static std::size_t GetComponentCount();

    VertexAttributeUtils() = delete;
};

} /* namespace glove */