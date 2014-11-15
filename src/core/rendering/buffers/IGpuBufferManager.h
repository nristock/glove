#pragma once

#include "core/GloveFwd.h"

#include <core/rendering/buffers/BufferUsage.h>

namespace glove {

class IGpuBufferManager {
  public:
    virtual ~IGpuBufferManager() {};

    /// @brief Creates a vertex buffer
    virtual IGpuBufferPtr CreateVertexBuffer(BufferUsage bufferUsage) = 0;

    /// @brief Creates an index buffer
    virtual IGpuBufferPtr CreateIndexBuffer() = 0;
};

} /* namespace glove */