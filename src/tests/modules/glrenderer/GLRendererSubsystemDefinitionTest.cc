#include <gmock/gmock.hpp>

#include <glove/rendering/IRenderSubsystem.hpp>

#include <modules/rendering/opengl/factories/GLRendererSubsystemFactory.hpp>
#include <modules/rendering/opengl/subsystem/GLRendererSubsystemDefinition.hpp>

namespace glove {
namespace gl {

class GLRendererSubsystemDefinitionTest : public ::testing::Test {
  protected:
    GLRendererSubsystemDefinition testDefinition;
};

TEST_F(GLRendererSubsystemDefinitionTest, SystemNameIsCorrect) {
    EXPECT_EQ("rnd_GLRenderer", testDefinition.GetSystemName());
}

TEST_F(GLRendererSubsystemDefinitionTest, SubsystemUuidIsCorrect) {
    EXPECT_EQ(
        SubsystemUuid({0x32, 0xcc, 0x29, 0x6b, 0xbb, 0xcd, 0x47, 0xb3, 0xbb, 0x02, 0x88, 0xbd, 0x01, 0xa6, 0x3d, 0xf7}),
        testDefinition.GetSystemUuid());
}

TEST_F(GLRendererSubsystemDefinitionTest, SystemTypeIsRenderingSystemType) {
    EXPECT_EQ(IRenderSubsystem::subsystemType, testDefinition.GetSystemType());
}

TEST_F(GLRendererSubsystemDefinitionTest, HasNoDependencies) {
    EXPECT_EQ(SubsystemTypeList(), testDefinition.GetSystemDependencies());
}

TEST_F(GLRendererSubsystemDefinitionTest, SubsystemFactoryIsInstanceOfGLRendererSubsystemFactory) {
    EXPECT_EQ(typeid(GLRendererSubsystemFactory), typeid(*testDefinition.GetSystemFactory().get()));
}
}
}