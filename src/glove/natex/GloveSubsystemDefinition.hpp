#pragma once

#include "glove/natex/Natex.hpp"
#include "glove/natex/ISubsystemDefinition.hpp"

namespace glove {

/// @brief Default implementation of ISubsystemDefinition which can be used by native extensions for convenience.
class GLOVE_API_EXPORT GloveSubsystemDefinition : public ISubsystemDefinition {
  public:
    GloveSubsystemDefinition(const std::string& name, const SubsystemUuid& uuid, const SubsystemType& type,
                             const SubsystemTypeList& dependencies, const ISubsystemFactoryPtr& subsystemFactory);
    virtual ~GloveSubsystemDefinition();

    virtual const std::string& GetSystemName();
    virtual const SubsystemUuid& GetSystemUuid();
    virtual const SubsystemType& GetSystemType();
    virtual const SubsystemTypeList& GetSystemDependencies();
    virtual const ISubsystemFactoryPtr& GetSystemFactory();

  private:
    const std::string name;
    const SubsystemUuid uuid;
    const SubsystemType type;

    const SubsystemTypeList dependencies;

    const ISubsystemFactoryPtr factory;
};
} /* namespace glove */