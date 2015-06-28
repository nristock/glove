#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/services/BasicService.hpp"
#include "glove/math/IntRect.hpp"

namespace BlueDwarf {
class RenderHardwareInterface;

class BD_API_EXPORT RendererService : public BasicService {
  public:
    static ServiceType Type;

    RendererService() : BasicService(Type) {}

    virtual std::shared_ptr<RenderHardwareInterface> GetRenderHardwareInterface() const = 0;
};
} // namespace BlueDwarf
