#pragma once

#include <core/GloveFwd.h>
#include <core/rendering/factories/IRendererFactory.h>

#include "../subsystem/OpenGLRendererModule.h"

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