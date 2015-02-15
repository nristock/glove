#include <gmock/gmock.hpp>

#include <glove/rendering/IRenderSubsystem.hpp>

#include <modules/rendering/opengl/subsystem/GLRendererSubsystem.hpp>
#include <modules/rendering/opengl/factories/GLGpuBufferFactory.hpp>
#include <modules/rendering/opengl/factories/GLMeshFactory.hpp>
#include <modules/rendering/opengl/factories/GLRendererFactory.hpp>
#include <modules/rendering/opengl/factories/GLShaderFactory.hpp>
#include <modules/rendering/opengl/factories/GLShaderProgramFactory.hpp>
#include <modules/rendering/opengl/factories/GLMaterialFactory.hpp>

#include "tests/modules/glrenderer/mock/MockRenderer.hpp"
#include "tests/modules/glrenderer/mock/MockGloveCore.hpp"
#include "tests/modules/glrenderer/mock/MockEventBus.hpp"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::ReturnRef;

namespace glove {
namespace gl {

class GLRendererSubsystemTest : public ::testing::Test {
  protected:
    IRendererPtr renderer;
    GLRendererSubsystemPtr testSubsystem;

    GLRendererSubsystemTest() : renderer(new MockRenderer()) {
        EventBusPtr eventBus(new MockEventBus());

        testSubsystem = GLRendererSubsystemPtr(new GLRendererSubsystem(eventBus));
    }
};

TEST_F(GLRendererSubsystemTest, GpuBufferFactoryIsOfTypeGLGpuBufferFactory) {
    EXPECT_EQ(typeid(GLGpuBufferFactory), typeid(*testSubsystem->GetGpuBufferFactory(renderer).get()));
}

TEST_F(GLRendererSubsystemTest, MeshFactoryIsOfTypeGLMeshFactory) {
    EXPECT_EQ(typeid(GLMeshFactory), typeid(*testSubsystem->GetMeshFactory(renderer).get()));
}

TEST_F(GLRendererSubsystemTest, RendererFactoryIsOfTypeGLRendererFactory) {
    EXPECT_EQ(typeid(GLRendererFactory), typeid(*testSubsystem->GetRendererFactory().get()));
}

TEST_F(GLRendererSubsystemTest, ShaderFactoryIsOfTypeGLShaderFactory) {
    EXPECT_EQ(typeid(GLShaderFactory), typeid(*testSubsystem->GetShaderFactory(renderer).get()));
}

TEST_F(GLRendererSubsystemTest, ShaderProgramFactoryIsOfTypeGLShaderProgramFactory) {
    EXPECT_EQ(typeid(GLShaderProgramFactory), typeid(*testSubsystem->GetShaderProgramFactory().get()));
}

TEST_F(GLRendererSubsystemTest, MaterialFactoryIsOfTypeGLMaterialFactory) {
    EXPECT_EQ(typeid(GLMaterialFactory), typeid(*testSubsystem->GetMaterialFactory().get()));
}
}
}