#include <gmock/gmock.hpp>
#include <glove/graph/Graph.hpp>
#include <glove/graph/gameobject/GameObject.hpp>
#include <glove/graph/Scenegraph.hpp>

#include "tests/graph/mock/GameObjectMock.hpp"
#include "tests/graph/mock/MockGameObjectFactory.hpp"

namespace glove {

class ScenegraphTest : public ::testing::Test {
  protected:
    Scenegraph scenegraph;
};

TEST_F(ScenegraphTest, InitialScenegraphIsEmpty) {
    ASSERT_EQ(0, scenegraph.GetGameObjectCount());
}

TEST_F(ScenegraphTest, InitializesCreatedGameObject) {
    GameObjectHandle goMock = GameObjectHandle(new GameObjectMock);
    EXPECT_CALL(*(GameObjectMock*)goMock.get(), Init()).Times(1);

    MockGameObjectFactory mockObjectFactory(goMock);
    auto gameObject = scenegraph.CreateGameObject(mockObjectFactory);
}

TEST_F(ScenegraphTest, CreateSimpleCreateGameObjectWithoutComponents) {
    auto gameObject = scenegraph.CreateSimpleGameObject();
    std::size_t objectComponentCount = 0;

    gameObject->IterateComponents([&](const GameComponentHandle&){++objectComponentCount;});

    EXPECT_EQ(0, objectComponentCount);
}

TEST_F(ScenegraphTest, AddsCreatedGameObjectsToGraph) {
    auto gameObject = scenegraph.CreateSimpleGameObject();

    ASSERT_EQ(1, scenegraph.GetGameObjectCount());
}

TEST_F(ScenegraphTest, CanCreateCustomGameObjects) {
    bool preInitCalled = false;
    bool postInitCalled = false;

    GameObjectHandle goMock = GameObjectHandle(new GameObjectMock);
    EXPECT_CALL(*(GameObjectMock*)goMock.get(), Init()).Times(1);

    MockGameObjectFactory mockObjectFactory(goMock);

    auto gameObject =
        scenegraph.CreateGameObject(mockObjectFactory, [&](const GameObjectHandle&) { preInitCalled = true; },
                                    [&](const GameObjectHandle&) { postInitCalled = true; });

    EXPECT_TRUE(preInitCalled);
    EXPECT_TRUE(postInitCalled);
}


}