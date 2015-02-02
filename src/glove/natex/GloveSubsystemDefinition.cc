#include "GloveSubsystemDefinition.h"

namespace glove {

GloveSubsystemDefinition::GloveSubsystemDefinition(const std::string& name, const SubsystemUuid& uuid,
                                                   const SubsystemType& type, const SubsystemTypeList& dependencies,
                                                   const ISubsystemFactoryPtr& subsystemFactory)
    : name(name), uuid(uuid), type(type), dependencies(dependencies), factory(subsystemFactory) {
}

GloveSubsystemDefinition::~GloveSubsystemDefinition() {
}

const std::string& GloveSubsystemDefinition::GetSystemName() {
    return name;
}

const SubsystemUuid& GloveSubsystemDefinition::GetSystemUuid() {
    return uuid;
}

const SubsystemType& GloveSubsystemDefinition::GetSystemType() {
    return type;
}

const SubsystemTypeList& GloveSubsystemDefinition::GetSystemDependencies() {
    return dependencies;
}

const ISubsystemFactoryPtr& GloveSubsystemDefinition::GetSystemFactory() {
    return factory;
}
}