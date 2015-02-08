#include <glove/natex/ISubsystemDefinitionRegistry.h>

#include "subsystem/GLRendererExtension.h"

namespace glove {
namespace gl {

const ExtensionUuid GLRendererExtension::extensionUuid = {0xd1, 0xd8, 0x2f, 0x90, 0x81, 0xcd, 0x41, 0xe2,
                                                          0x8d, 0x30, 0x2e, 0xb7, 0xdf, 0x27, 0xb2, 0xa1};
const std::string GLRendererExtension::extensionName = "mod_GLRenderer";

GLRendererExtension::GLRendererExtension() : subsystemDefinition(new GLRendererSubsystemDefinition()) {
}

const ExtensionUuid GLRendererExtension::GetExtensionUuid() const {
    return extensionUuid;
}

const std::string& GLRendererExtension::GetExtensionName() const {
    return extensionName;
}

void GLRendererExtension::RegisterSubsystems(const ISubsystemDefinitionRegistryPtr& subsystemRegistry) {
    subsystemRegistry->RegisterSubsystemType(subsystemDefinition->GetSystemType());
    subsystemRegistry->RegisterSubsystemDefinition(subsystemDefinition);
}
}
}