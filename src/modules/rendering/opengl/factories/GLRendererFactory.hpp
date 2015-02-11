#pragma once

#include <glove/GloveFwd.hpp>
#include <glove/rendering/factories/IRendererFactory.hpp>

#include "subsystem/OpenGLRendererModule.hpp"

namespace glove {
namespace gl {

/// @ingroup Factories
class GLRendererFactory : public IRendererFactory {
  public:
    GLRendererFactory(const EventBusPtr& eventBus);

    virtual IRendererPtr CreateRenderer(const WindowConstructionHints& windowDescription);

  private:
    EventBusPtr eventBus;
    ContextId nextContextId;
};
}
} /* namespace glove */