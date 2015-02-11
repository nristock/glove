#pragma once

#include <cstddef>
#include "glove/rendering/buffers/BufferUsage.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IGpuBuffer {
  public:
    virtual ~IGpuBuffer(){};

    /// @brief Binds the buffer for use. Could be called multiple times per frame.
    virtual void Bind() = 0;

    /// @brief Unbinds the buffer. Could be called multiple times per frame and potentially without binding this
    ///        specific buffer first.
    virtual void Unbind() = 0;

    virtual void WriteData(std::size_t sizeInBytes, const void* data) = 0;
};

} /* namespace glove */
