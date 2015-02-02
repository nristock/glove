#pragma once

#include "glove/rendering/Rendering.h"
#include "glove/rendering/buffers/BufferUsage.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IGpuBufferFactory {
  public:
    virtual ~IGpuBufferFactory(){};

    virtual IGpuBufferPtr CreateVertexBuffer(BufferUsage bufferUsage) const = 0;
    virtual IGpuBufferPtr CreateIndexBuffer() const = 0;
};
}