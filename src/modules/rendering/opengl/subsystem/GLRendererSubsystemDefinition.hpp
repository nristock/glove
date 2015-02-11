#pragma once

#include <glove/natex/ISubsystemDefinition.hpp>

namespace glove {
namespace gl {

/// @ingroup OpenGLRenderer
class GLRendererSubsystemDefinition : public ISubsystemDefinition {
  public:
    GLRendererSubsystemDefinition();

    virtual const std::string& GetSystemName();
    virtual const SubsystemUuid& GetSystemUuid();
    virtual const SubsystemType& GetSystemType();
    virtual const SubsystemTypeList& GetSystemDependencies();
    virtual const ISubsystemFactoryPtr& GetSystemFactory();

  private:
    static const std::string subsystemName;
    static const SubsystemUuid subsystemUuid;
    static const SubsystemTypeList dependencies;

    ISubsystemFactoryPtr rendererFactory;
};
}
} /* namespace glove */