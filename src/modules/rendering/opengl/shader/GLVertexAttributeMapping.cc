#include "GLVertexAttributeMapping.h"

#include <glove/GloveException.h>

namespace glove {
namespace gl {

uint32_t GLVertexAttributeMapping::GetAttributeLocation(VertexAttributeSemantic semantic) {
    if (attributeMappings.count(semantic)) {
        return (uint32_t)attributeMappings[semantic];
    }

    throw GLOVE_EXCEPTION("Semantic has not been mapped.");
}

void GLVertexAttributeMapping::MapAttribute(VertexAttributeSemantic semantic, uint32_t location) {
    attributeMappings[semantic] = location;
}
}
}