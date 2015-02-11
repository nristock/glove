#pragma once

#include <cstddef>

#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IVertexData {
  public:
    virtual ~IVertexData(){};

    virtual const std::size_t GetGpuBufferCount() const = 0;
    virtual const IGpuBufferPtr& GetGpuBuffer(std::size_t bufferIndex) const = 0;
    virtual const VertexLayout& GetVertexLayout() const = 0;
    virtual const std::size_t GetVertexCount() const = 0;
    virtual void BindAllBuffers() = 0;
};
}