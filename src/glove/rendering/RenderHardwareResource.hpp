#pragma once

#include "glove/GloveApi.hpp"

namespace glove {
/**
* Base class for all render hardware resources. This class is non-copyable to ensure that resource aren't cleaned up
* twice or too soon by accidental copies.
*/
class GLOVE_API_EXPORT RenderHardwareResource {
  public:
    RenderHardwareResource(RenderHardwareResource&&) = default;
    RenderHardwareResource(const RenderHardwareResource&) = delete;

    virtual ~RenderHardwareResource() = default;

    RenderHardwareResource& operator=(const RenderHardwareResource&) = delete;

  protected:
    RenderHardwareResource() = default;
};

} /* namespace glove */