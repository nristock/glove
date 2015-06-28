#pragma once

#include <glove/rendering/VertexBinding.hpp>

#include "../internal/OpenGLWrapper.hpp"

namespace glove {
class VertexBuffer;
using VertexBufferHandle = std::shared_ptr<VertexBuffer>;

namespace gl {
/**
* The OpenGL renderer implementation of a VertexBinding.
*/
class GLOVE_API_EXPORT GLVertexBinding : public VertexBinding {
  public:
    GLVertexBinding(const std::unordered_map<uint8, VertexElement>& shaderAttributeBindings,
                    const std::vector<VertexBufferHandle>& vertexStreams);
    virtual ~GLVertexBinding();

    GLuint GetVaoId() const { return vaoId; }

  private:
    void InitVao();

    GLuint vaoId = 0;
};
}
} /* namespace glove */