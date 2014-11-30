#include "GLRendererSubsystemDefinition.h"

#include <core/rendering/IRenderSubsystem.h>

#include "../factories/GLRendererSubsystemFactory.h"

namespace glove {
namespace gl {

const std::string GLRendererSubsystemDefinition::subsystemName = "rnd_GLRenderer";
const SubsystemUuid GLRendererSubsystemDefinition::subsystemUuid = {0x32, 0xcc, 0x29, 0x6b, 0xbb, 0xcd, 0x47, 0xb3,
                                                                    0xbb, 0x02, 0x88, 0xbd, 0x01, 0xa6, 0x3d, 0xf7};
const SubsystemTypeList GLRendererSubsystemDefinition::dependencies;

GLRendererSubsystemDefinition::GLRendererSubsystemDefinition() : rendererFactory(new GLRendererSubsystemFactory()) {
}

const std::string& GLRendererSubsystemDefinition::GetSystemName() {
    return subsystemName;
}

const SubsystemUuid& GLRendererSubsystemDefinition::GetSystemUuid() {
    return subsystemUuid;
}

const SubsystemType& GLRendererSubsystemDefinition::GetSystemType() {
    return IRenderSubsystem::subsystemType;
}

const SubsystemTypeList& GLRendererSubsystemDefinition::GetSystemDependencies() {
    return dependencies;
}

const ISubsystemFactoryPtr& GLRendererSubsystemDefinition::GetSystemFactory() {
    return rendererFactory;
}

}
}