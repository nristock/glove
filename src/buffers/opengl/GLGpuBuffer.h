#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include <pitamem/MemoryProfile.h>
#include "buffers/IGpuBuffer.h"

namespace glove {

/** This class implements a GL hardware/GPU buffer */
class GLGpuBuffer : public IGpuBuffer {
Profilable();
public:
    GLGpuBuffer(BufferUsage usage, GLenum target);

    virtual ~GLGpuBuffer();

    virtual void Bind();

    virtual void Unbind();

    virtual void WriteData(size_t sizeInBytes, const void* data);

protected:
    /** Buffer object ID */
    GLuint bufferId;

    /** The buffer binding target */
    GLenum target;

    /** The buffer's intended usage */
    BufferUsage usage;
};


} // namespace glove