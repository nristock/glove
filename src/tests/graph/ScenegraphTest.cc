#include <vendor/gmock/gmock.h>
#include <vendor/gtest/gtest.h>
#include <core/graph/Scenegraph.h>
#include <core/graph/GameObject.h>
#include "tests/graph/mock/GameObjectMock.h"

namespace glove {

class ScenegraphTest : public ::testing::Test {
protected:
    Scenegraph scenegraph;
};

TEST_F(ScenegraphTest, InitialScenegraphIsEmpty) {
    ASSERT_EQ(0, scenegraph.GetGameObjectCount());
}

TEST_F(ScenegraphTest, InitializesCreatedGameObject) {
    GameObjectMock* goMock = new GameObjectMock;
    EXPECT_CALL(*goMock, Init()).Times(1);

    auto gameObject = scenegraph.CreateGameObject<GameObjectMock>(
            [&]() {
                return goMock;
            }
    );
}

TEST_F(ScenegraphTest, AddsCreatedGameObjectsToGraph) {
    auto gameObject = scenegraph.CreateSimpleGameObject();

    ASSERT_EQ(1, scenegraph.GetGameObjectCount());
}

TEST_F(ScenegraphTest, CanCreateCustomGameObjects) {
    bool allocatorCalled = false;
    bool preInitCalled = false;
    bool postInitCalled = false;

    auto gameObject = scenegraph.CreateGameObject<GameObject>(
            [&]() {
                allocatorCalled = true;
                return new GameObject();
            },
            [&](GameObjectPointer go) {
                preInitCalled = true;
            },
            [&](GameObjectPointer go) {
                postInitCalled = true;
            });

    ASSERT_TRUE(allocatorCalled);
    ASSERT_TRUE(preInitCalled);
    ASSERT_TRUE(postInitCalled);
}

TEST_F(ScenegraphTest, CanSetMainCamera) {
    auto camera = scenegraph.CreateCamera();
    scenegraph.SetActiveCamera(camera);

    ASSERT_EQ(camera, scenegraph.GetMainCamera());
}

}