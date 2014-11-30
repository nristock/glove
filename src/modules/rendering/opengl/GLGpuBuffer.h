#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include <core/rendering/buffers/IGpuBuffer.h>

namespace glove {
namespace gl {

/// @brief OpenGL GPU buffer implementation.
/// @ingroup OpenGLRenderer
class GLGpuBuffer : public IGpuBuffer {
  public:
    /// @brief Please refer to https://www.opengl.org/sdk/docs/man/html/glBindBuffer.xhtml for information on possible
    ///        binding targets.
    GLGpuBuffer(BufferUsage usage, GLenum target);
    GLGpuBuffer(const GLGpuBuffer&) = delete;
    virtual ~GLGpuBuffer();

    GLGpuBuffer& operator=(const GLGpuBuffer&) = delete;

    virtual void Bind();
    virtual void Unbind();
    virtual void WriteData(size_t sizeInBytes, const void* data);

  protected:
    GLuint bufferId;
    GLenum target;
    BufferUsage usage;
};

}
} // namespace glove