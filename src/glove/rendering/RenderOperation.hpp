#pragma once

#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @brief A structure representing a single render operation for passive rendering.
/// @ingroup RenderSubsystemInterface
///
/// It is the renderer's responsibility to make sure the provided vertex/index data and material are valid and in a
/// suitable state (i.e. pipeline binding states, etc.)
struct GLOVE_API_EXPORT RenderOperation {
  public:
    /// @brief Resets the structure by setting all members to nullptr
    void Reset();

    /// @brief Vertex data to use for rendering (must not be null)
    IVertexData* vertexData;
    /// @brief Index data to use for rendering (can be null)
    IIndexData* indexData;
    /// @brief Material to use for rendering (must not be null)
    IMaterial* material;
};

} // namespace glove