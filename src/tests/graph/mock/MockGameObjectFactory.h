#pragma once

#include <core/graph/gameobject/factories/IGameObjectFactory.h>
#include <core/graph/Graph.h>

namespace glove {
class MockGameObjectFactory : public IGameObjectFactory{
public:
    MockGameObjectFactory(GameObjectHandle& gameObject);
    virtual GameObjectHandle Create();

private:
    GameObjectHandle gameObject;
};
}