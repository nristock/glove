#include <gmock/gmock.hpp>

#include <glove/natex/Natex.hpp>
#include <glove/rendering/IRenderSubsystem.hpp>
#include <modules/rendering/opengl/subsystem/GLRendererExtension.hpp>

#include "tests/modules/glrenderer/mock/MockSubsystemDefinitionRegistry.hpp"

using ::testing::_;

namespace glove {
namespace gl {

class GLRendererExtensionTest : public ::testing::Test {
  protected:
    ISystemExtensionPtr rendererExtension;

    GLRendererExtensionTest() : rendererExtension(new GLRendererExtension()) {}
};

TEST_F(GLRendererExtensionTest, ExtensionUuidIsCorrect) {
    EXPECT_EQ(
        ExtensionUuid({0xd1, 0xd8, 0x2f, 0x90, 0x81, 0xcd, 0x41, 0xe2, 0x8d, 0x30, 0x2e, 0xb7, 0xdf, 0x27, 0xb2, 0xa1}),
        rendererExtension->GetExtensionUuid());
}

TEST_F(GLRendererExtensionTest, ExtensionNameIsCorrect) {
    EXPECT_EQ("mod_GLRenderer", rendererExtension->GetExtensionName());
}

TEST_F(GLRendererExtensionTest, RegistersRenderingSystemTypeAndGLRendererSubsystemDefinition) {
    ISubsystemDefinitionRegistryPtr subsystemRegistry(new MockSubsystemDefinitionRegistry);

    EXPECT_CALL(*(MockSubsystemDefinitionRegistry*)subsystemRegistry.get(),
                RegisterSubsystemType(IRenderSubsystem::subsystemType)).Times(1);
    EXPECT_CALL(*(MockSubsystemDefinitionRegistry*)subsystemRegistry.get(), RegisterSubsystemDefinition(_)).Times(1);

    rendererExtension->RegisterSubsystems(subsystemRegistry);
}
}
}