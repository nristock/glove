#pragma once

#include <glove/rendering/GpuBuffer.hpp>

#include "internal/OpenGLWrapper.hpp"

namespace BlueDwarf {
namespace gl {

/**
* Utilities to convert between engine specific data structures and OpenGL structures.
*/
class GLBufferUtils {
  public:
    GLBufferUtils() = delete;
    ~GLBufferUtils() = delete;

    static GLenum BufferMapModeToGlAccessMode(BufferMappingMode mappingMode);
};

/**
* This convenience base class abstracts common buffer operations like creation, deletion, binding and client memory
* mapping.
*
* GPU buffer resources should not be copyable since destruction will release the GL resource.
*/
class GLGpuBufferBase {
  public:
    /// Deletes the buffer.
    virtual ~GLGpuBufferBase() { GL::DeleteBuffers(1, &bufferObjectId); }

    /// Non-copyable
    GLGpuBufferBase(const GLGpuBufferBase&) = delete;
    /// Non-copyable
    GLGpuBufferBase& operator=(const GLGpuBufferBase&) = delete;

    /// Binds the buffer to the  GL buffer target specified on construction.
    void GLBind() const { GL::BindBuffer(target, bufferObjectId); }

    /**
    * Maps the buffer to client memory.
    *
    * @return Returns a pointer to the beginning of the mapped buffer.
    */
    void* GLMap(BufferMappingMode mapMode) {
        GLBind();
        return GL::MapBuffer(target, GLBufferUtils::BufferMapModeToGlAccessMode(mapMode));
    }

    /// Flushes the mapped buffer and unmaps it.
    void GLUnmap() {
        GLBind();
        GL::UnmapBuffer(target);
    }

    void GLStore(std::size_t sizeInBytes, void* data) {
        GLBind();
        GL::BufferData(target, sizeInBytes, data, GL_STATIC_DRAW);
    }

  protected:
    /**
    * No GLGpuBufferBase instance should be created. This class is supposed to be derived from.
    *
    * @param target [in] The GL buffer traget to which this buffer will be bound.
    */
    GLGpuBufferBase(GLenum target) : target(target) { GL::GenBuffers(1, &bufferObjectId); }

    GLenum target;
    GLuint bufferObjectId;
};

/**
* The OpenGL renderer's implementation of a VertexBuffer.
*/
class GLVertexBuffer : public VertexBuffer, public GLGpuBufferBase {
  public:
    GLVertexBuffer() : GLGpuBufferBase(GL_ARRAY_BUFFER) {}

    virtual void* Map(BufferMappingMode mapMode) { return GLMap(mapMode); }
    virtual void Unmap() { GLUnmap(); }
    virtual void Store(std::size_t sizeInBytes, void* data) {GLStore(sizeInBytes, data);}
};

/**
* The OpenGL renderer's implementation of an IndexBuffer.
*/
class GLIndexBuffer : public IndexBuffer, public GLGpuBufferBase {
  public:
    GLIndexBuffer() : GLGpuBufferBase(GL_ELEMENT_ARRAY_BUFFER) {}

    virtual void* Map(BufferMappingMode mapMode) { return GLMap(mapMode); }
    virtual void Unmap() { GLUnmap(); }
    virtual void Store(std::size_t sizeInBytes, void* data) {GLStore(sizeInBytes, data);}
};
}
} /* namespace BlueDwarf */