#pragma once

#include "glove/GloveApi.hpp"
#include "glove/services/BasicService.hpp"
#include "glove/math/IntRect.hpp"

namespace glove {
class RenderHardwareInterface;

class GLOVE_API_EXPORT RendererService : public BasicService {
  public:
    static ServiceType Type;

    RendererService() : BasicService(Type) {}

    virtual std::shared_ptr<RenderHardwareInterface> GetRenderHardwareInterface() const = 0;
};
} // namespace glove
