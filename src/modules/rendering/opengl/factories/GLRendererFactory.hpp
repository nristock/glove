#pragma once

#include <glove/GloveFwd.hpp>
#include <glove/rendering/factories/IRendererFactory.hpp>
#include <glove/services/Services.hpp>

#include "subsystem/OpenGLRendererModule.hpp"

namespace glove {
namespace gl {

/// @ingroup Factories
class GLRendererFactory : public IRendererFactory {
  public:
    GLRendererFactory();

    virtual IRendererPtr CreateRenderer(const WindowConstructionHints& windowDescription);
    virtual bool Init(ServiceRegistry &serviceRegistry) override;

  private:
    EventBusPtr eventBus;
    ContextId nextContextId;
};
}
} /* namespace glove */