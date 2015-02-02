#pragma once

#include <stdint.h>

#include "glove/rendering/vertex/VertexAttributeSemantic.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IVertexAttributeMapping {
  public:
    virtual ~IVertexAttributeMapping() = default;

    virtual uint32_t GetAttributeLocation(VertexAttributeSemantic semantic) = 0;
    virtual void MapAttribute(VertexAttributeSemantic semantic, uint32_t attributeLocation) = 0;
};
}