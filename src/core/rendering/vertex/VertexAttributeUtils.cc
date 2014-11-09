#include "VertexAttributeUtils.h"

#include <core/GloveException.h>

namespace glove {


VertexAttributeUtils::VertexAttributeUtils() {

}

std::size_t VertexAttributeUtils::GetAttributeTypeSize(VertexAttributeType attributeType) {
    switch (attributeType) {
        case VAT_FLOAT3:
            return 3 * sizeof(float);
        case VAT_FLOAT4:
            return 4 * sizeof(float);
    }

    throw GLOVE_EXCEPTION("Unexpected control flow in VertexAttribute::GetSize");
}
}