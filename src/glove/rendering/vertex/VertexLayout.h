#pragma once

#include <list>
#include <cstddef>
#include <cstring>

#include "glove/GloveFwd.hpp"
#include "glove/rendering/Rendering.h"
#include "glove/rendering/vertex/VertexAttribute.h"

namespace glove {

/// @brief Represents a vertex layout definition
/// @ingroup RenderSubsystemInterface
///
/// A vertex layout is a collection of VertexAttributes. This class does also automatically calculate the stride
/// (the bytes between two elements) per buffer.
class VertexLayout {
  public:
    VertexLayout() = default;

    /// @brief Adds a VertexAttribute element to the internal list of vertex attributes and recalculates the stride
    ///        for the affected buffer.
    GLOVE_INLINE void AddAttribute(const VertexAttribute& element);

    GLOVE_INLINE std::size_t GetAttributeCount() const;

    GLOVE_INLINE const VertexAttribute& GetAttribute(std::size_t index) const;

    GLOVE_INLINE const std::size_t GetStrideForBufferIndex(std::size_t bufferIndex);

    /// @brief Equality is determined by the equality of the underlying VertexAttributeList (VertexLayout::attributes)
    GLOVE_INLINE bool operator==(const VertexLayout& other) const;

  private:
    typedef std::list<VertexAttribute> VertexAttributeList;
    typedef std::map<std::size_t, std::size_t> AttributeStrideMap;

    VertexAttributeList attributes;
    AttributeStrideMap strideMap;
};

} // namespace glove