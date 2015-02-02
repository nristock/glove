#pragma once

#include <glove/GloveFwd.hpp>
#include <glove/natex/ISubsystemFactory.h>

namespace glove {
namespace gl {

/// @ingroup Factories
class GLRendererSubsystemFactory : public ISubsystemFactory {
  public:
    virtual ISubsystemPtr CreateSubsystem(const GloveCorePtr& engineCore);
};
}
} /* namespace glove */