#pragma once

#include <core/GloveFwd.h>
#include <core/natex/ISubsystemFactory.h>

namespace glove {
namespace gl {

/// @ingroup Factories
class GLRendererSubsystemFactory : public ISubsystemFactory {
  public:
    virtual ISubsystemPtr CreateSubsystem(const GloveCorePtr& engineCore);
};
}
} /* namespace glove */