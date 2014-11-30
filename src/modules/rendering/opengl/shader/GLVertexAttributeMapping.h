#pragma once

#include <map>

#include <core/rendering/vertex/VertexAttributeSemantic.h>
#include <core/rendering/vertex/IVertexAttributeMapping.h>

namespace glove {
namespace gl {

/// @ingroup Shader
class GLVertexAttributeMapping : public IVertexAttributeMapping {
  public:
    virtual ~GLVertexAttributeMapping() = default;
    virtual uint32_t GetAttributeLocation(VertexAttributeSemantic semantic);
    virtual void MapAttribute(VertexAttributeSemantic semantic, uint32_t location);

  private:
    std::map<VertexAttributeSemantic, uint32_t> attributeMappings;
};
}
}