#pragma once

#include <cstddef>
#include <core/rendering/buffers/BufferUsage.h>

namespace glove {

/// @brief A class abstracting hardware/GPU buffers
class IGpuBuffer {
public:
    virtual ~IGpuBuffer() {};

    /// @brief Binds the buffer for use. Can be called multiple times per frame.
    virtual void Bind() = 0;

    /// @brief Unbinds the buffer. Can be called multiple times per frame.
    virtual void Unbind() = 0;

    /// @brief Writes data to the buffer and uploads it to the GPU
    virtual void WriteData(size_t sizeInBytes, const void* data) = 0;

};

} /* namespace glove */
