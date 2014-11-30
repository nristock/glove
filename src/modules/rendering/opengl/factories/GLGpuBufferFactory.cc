#include "GLGpuBufferFactory.h"

#include "../GLGpuBuffer.h"

namespace glove {
namespace gl {

IGpuBufferPtr GLGpuBufferFactory::CreateVertexBuffer(BufferUsage bufferUsage) const {
    return IGpuBufferPtr(new GLGpuBuffer(bufferUsage, GL_ARRAY_BUFFER));
}

IGpuBufferPtr GLGpuBufferFactory::CreateIndexBuffer() const {
    return IGpuBufferPtr(new GLGpuBuffer(BufferUsage::STATIC, GL_ELEMENT_ARRAY_BUFFER));
}
}
}