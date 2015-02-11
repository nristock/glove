#pragma once

#include "glove/rendering/Rendering.hpp"
#include "glove/rendering/buffers/BufferUsage.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IGpuBufferFactory {
  public:
    virtual ~IGpuBufferFactory(){};

    virtual IGpuBufferPtr CreateVertexBuffer(BufferUsage bufferUsage) const = 0;
    virtual IGpuBufferPtr CreateIndexBuffer() const = 0;
};
}