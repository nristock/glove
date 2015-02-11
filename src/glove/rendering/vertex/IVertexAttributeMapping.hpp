#pragma once

#include <stdint.h>

#include "glove/rendering/vertex/VertexAttributeSemantic.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IVertexAttributeMapping {
  public:
    virtual ~IVertexAttributeMapping() = default;

    virtual uint32_t GetAttributeLocation(VertexAttributeSemantic semantic) = 0;
    virtual void MapAttribute(VertexAttributeSemantic semantic, uint32_t attributeLocation) = 0;
};
}