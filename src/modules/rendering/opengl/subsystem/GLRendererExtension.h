#pragma once

#include <glove/GloveFwd.hpp>
#include <glove/natex/ISystemExtension.h>

#include "OpenGLRendererModule.h"
#include "GLRendererSubsystemDefinition.h"

namespace glove {
namespace gl {

/// @ingroup OpenGLRenderer
class GLRendererExtension : public ISystemExtension {
  public:
    GLRendererExtension();

    virtual void RegisterSubsystems(const ISubsystemDefinitionRegistryPtr& subsystemRegistry);

    virtual const ExtensionUuid GetExtensionUuid() const;
    virtual const std::string& GetExtensionName() const;

  private:
    static const ExtensionUuid extensionUuid;
    static const std::string extensionName;

    ISubsystemDefinitionPtr subsystemDefinition;
};
}
} /* namespace glove */