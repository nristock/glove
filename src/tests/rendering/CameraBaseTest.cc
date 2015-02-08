#include <vendor/gmock/gmock.h>

#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glove/graph/gameobject/factories/EmptyGameObjectFactory.h>
#include <glove/graph/gameobject/GameObject.h>
#include <glove/graph/Transform.h>

#include "mock/MockCamera.h"

using testing::_;
using testing::Invoke;

namespace glove {
TEST(CameraBaseTest, RecalculatesMatrixOnAttach) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(2, 100);

    GameObjectHandle owner = EmptyGameObjectFactory::CreateEmpty();
    owner->GetTransform().SetPosition(glm::vec3(distribution(generator), distribution(generator), distribution(generator)));

    CameraBaseHandle camera = CameraBaseHandle(new MockCamera());
    camera->OnAttach(owner);

    EXPECT_EQ(owner->GetTransform().GetGlobalTransform(), camera->GetViewProjectionMatrix());
}

TEST(CameraBaseTest, RecalculatesMatrixIfOwnerIsMoved) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(2, 100);

    GameObjectHandle owner = EmptyGameObjectFactory::CreateEmpty();

    CameraBaseHandle camera = CameraBaseHandle(new MockCamera());
    camera->OnAttach(owner);

    owner->GetTransform().SetPosition(glm::vec3(distribution(generator), distribution(generator), distribution(generator)));

    EXPECT_EQ(owner->GetTransform().GetGlobalTransform(), camera->GetViewProjectionMatrix());
}

TEST(CameraBaseTest, InvokesRecalculateProjectionMatrixWhenAspectRatioIsSet) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(2, 100);

    float aspectRatio = distribution(generator);

    CameraBaseHandle camera = CameraBaseHandle(new MockCamera());
    EXPECT_CALL(*(MockCamera*)camera.get(), RecalculateProjectionMatrix()).Times(1);
    dynamic_cast<MockCamera*>(camera.get())->SetAspectRatioBase(aspectRatio);
}

}