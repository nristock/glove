#pragma once

#include <cstddef>

#include "glove/GloveApi.hpp"
#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IIndexData {
  public:
    virtual ~IIndexData() = default;

    virtual const std::size_t GetIndexCount() const = 0;
    virtual const IGpuBufferPtr& GetGpuBuffer() const = 0;
    virtual void BindBuffer() = 0;
};
}