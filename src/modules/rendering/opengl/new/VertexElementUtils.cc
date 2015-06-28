#include "VertexElementUtils.hpp"

namespace glove {
namespace gl {

GLenum VertexElementTypeToGlType(const VertexElementType& elementType) {
    switch(elementType) {
        case VertexElementType::Float1:
        case VertexElementType::Float2:
        case VertexElementType::Float3:
            return GL_FLOAT;

        default:
            return GL_NONE;
    }
}

GLint VertexElementTypeToElementCount(const VertexElementType& elementType) {
    switch(elementType) {
        case VertexElementType::Float1:
            return 1;
        case VertexElementType::Float2:
            return 2;
        case VertexElementType::Float3:
            return 3;

        default:
            return 0;
    }
}

}
} /* namespace glove */