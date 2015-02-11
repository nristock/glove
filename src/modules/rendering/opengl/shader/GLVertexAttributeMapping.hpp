#pragma once

#include <map>
#include <glove/rendering/vertex/IVertexAttributeMapping.hpp>

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