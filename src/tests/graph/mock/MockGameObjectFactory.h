#pragma once

#include <glove/graph/gameobject/factories/IGameObjectFactory.h>
#include <glove/graph/Graph.h>

namespace glove {
class MockGameObjectFactory : public IGameObjectFactory{
public:
    MockGameObjectFactory(GameObjectHandle& gameObject);
    virtual GameObjectHandle Create();

private:
    GameObjectHandle gameObject;
};
}