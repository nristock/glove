#include "GLGpuBuffer.h"

#include "internal/OpenGLWrapper.h"

namespace glove {
namespace gl {

GLGpuBuffer::GLGpuBuffer(BufferUsage usage, GLenum target) : IGpuBuffer(), target(target), usage(usage) {
    GL::GenBuffers(1, &bufferId);
}

GLGpuBuffer::~GLGpuBuffer() {
    GL::DeleteBuffers(1, &bufferId);
}

void GLGpuBuffer::Bind() {
    GL::BindBuffer(target, bufferId);
}

void GLGpuBuffer::Unbind() {
    GL::BindBuffer(target, 0);
}

void GLGpuBuffer::WriteData(size_t sizeInBytes, const void* data) {
    Bind();

    switch (usage) {
    case BufferUsage::STATIC:
        GL::BufferData(target, sizeInBytes, data, GL_STATIC_DRAW);
        break;
    case BufferUsage::DYNAMIC:
        GL::BufferData(target, sizeInBytes, data, GL_DYNAMIC_DRAW);
        break;
    }
}

}
} // namespace glove