#pragma once

#include <glove/rendering/VertexLayout.hpp>

#include "internal/OpenGLWrapper.hpp"

namespace glove {
namespace gl {
/**
* Transforms a VertexElementType into the corresponding OpenGL data type.
*
* E.g. A Float3 is composed of three floats so this function would return GL_FLOAT.
*/
GLenum VertexElementTypeToGlType(const VertexElementType& elementType);

/**
* Returns the number of components of a VertexElementType.
*
* E.g. A Float3 has three floats so this function would return 3.
*/
GLint VertexElementTypeToElementCount(const VertexElementType& elementType);
}
} /* namespace glove */