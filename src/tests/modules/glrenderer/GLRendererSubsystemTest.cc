#include <vendor/gmock/gmock.h>

#include <glove/rendering/IRenderSubsystem.h>

#include <subsystem/GLRendererSubsystem.h>
#include <factories/GLGpuBufferFactory.h>
#include <factories/GLMeshFactory.h>
#include <factories/GLRendererFactory.h>
#include <factories/GLShaderFactory.h>
#include <factories/GLShaderProgramFactory.h>
#include <factories/GLMaterialFactory.h>

#include "mock/MockRenderer.h"
#include "mock/MockGloveCore.h"
#include "mock/MockEventBus.h"

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
        GloveCorePtr gloveCore(new MockGloveCore());
        EventBusPtr eventBus(new MockEventBus());
        EXPECT_CALL(*(MockGloveCore*)gloveCore.get(), GetEventBus()).WillRepeatedly(ReturnRef(eventBus));

        testSubsystem = GLRendererSubsystemPtr(new GLRendererSubsystem(gloveCore));
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