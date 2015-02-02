#pragma once

#include <cstddef>

#include "glove/rendering/Rendering.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IIndexData {
  public:
    virtual ~IIndexData() = default;

    virtual const std::size_t GetIndexCount() const = 0;
    virtual const IGpuBufferPtr& GetGpuBuffer() const = 0;
    virtual void BindBuffer() = 0;
};
}