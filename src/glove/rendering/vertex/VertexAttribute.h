#pragma once

#include <cstddef>

#include "glove/GloveFwd.hpp"
#include "glove/rendering/vertex/VertexAttributeSemantic.h"
#include "glove/rendering/vertex/VertexAttributeType.h"

namespace glove {

/// @brief Holds all vital information about a single VertexAttribute in a VertexLayout.
/// @ingroup RenderSubsystemInterface
class VertexAttribute {
  public:
    /// @param [in] binding The buffer index this attribute belongs to (relates to the buffer index in VertexData)
    /// @param [in] offset The attribute's offset in bytes.
    VertexAttribute(std::size_t bufferIndex, std::size_t offset, VertexAttributeType dataType,
                    VertexAttributeSemantic semantic);

    std::size_t GetBufferIndex() const;
    std::size_t GetByteOffset() const;
    VertexAttributeType GetType() const;
    VertexAttributeSemantic GetSemantic() const;

    /// @brief Returns the number of individual components - e.g. FLOAT3 has 3 float components.
    ///        The number of components is determined using VertexAttributeUtils.
    std::size_t GetNumberOfComponents() const;
    std::size_t GetSizeInBytes() const;
    bool operator==(const VertexAttribute& other) const;

  private:
    /// @brief The buffer index (also called buffer binding slot)
    ///
    /// It is possible to provide vertex data using multiple GPU buffers and thus separating data which has to be
    /// updated often from rarely updated data. IVertexData provides a method to get a GPU buffer by its index which
    /// directly corresponds to the buffer index specified here.
    size_t bufferIndex;

    /// @brief Byte offset of this attribute from the beginning of a vertex.
    ///
    /// Assume the following VertexLayout:
    ///    position  : FLOAT3
    ///    color     : FLOAT4
    /// Position is the first attribute and thus does not have an offset from the beginning. Color on the other hand has
    /// an offset of 3 * sizeof(float).
    size_t offset;

    VertexAttributeType dataType;
    VertexAttributeSemantic semantic;
};

} // namespace glove