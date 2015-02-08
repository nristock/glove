#include <vendor/gmock/gmock.h>

#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glove/rendering/gamecomponent/OrthoCamera.h>
#include <glove/graph/gameobject/factories/EmptyGameObjectFactory.h>
#include <glove/graph/gameobject/GameObject.h>

#include "mock/MockVertexData.h"
#include "mock/MockIndexData.h"
#include "mock/MockMesh.h"

namespace glove {
TEST(OrthoCameraTest, CalculatesOrthoMatrix) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(2, 100);

    float orthoSize = distribution(generator);
    float aspectRatio = distribution(generator);

    GameObjectHandle owner = EmptyGameObjectFactory::CreateEmpty();

    CameraBaseHandle camera = CameraBaseHandle(new GameComponents::OrthoCamera(orthoSize, aspectRatio));
    glm::mat4 expectedProjectionMatrix = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio);

    owner->AddComponent(camera);

    EXPECT_EQ(expectedProjectionMatrix, camera->GetViewProjectionMatrix());
}

TEST(OrthoCameraTest, RecalculatesOrthoMatrixIfAspectRatioIsSet) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(2, 100);

    float orthoSize = 1;
    float aspectRatio = distribution(generator);

    GameObjectHandle owner = EmptyGameObjectFactory::CreateEmpty();

    CameraBaseHandle camera = CameraBaseHandle(new GameComponents::OrthoCamera(1, 1));
    owner->AddComponent(camera);

    glm::mat4 expectedProjectionMatrix = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio);

    camera->SetAspectRatio(aspectRatio);

    EXPECT_EQ(expectedProjectionMatrix, camera->GetViewProjectionMatrix());
}

TEST(OrthoCameraTest, RecalculatesOrthoMatrixIfOrthoSizeIsSet) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(2, 100);

    float orthoSize = distribution(generator);
    float aspectRatio = 1;

    GameObjectHandle owner = EmptyGameObjectFactory::CreateEmpty();

    CameraBaseHandle camera = CameraBaseHandle(new GameComponents::OrthoCamera(1, 1));
    owner->AddComponent(camera);

    glm::mat4 expectedProjectionMatrix = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio);

    dynamic_cast<GameComponents::OrthoCamera*>(camera.get())->SetOrthoSize(orthoSize);

    EXPECT_EQ(expectedProjectionMatrix, camera->GetViewProjectionMatrix());
}

}