#pragma once

#include <glove/graph/gameobject/factories/IGameObjectFactory.hpp>
#include <glove/graph/Graph.hpp>

namespace glove {
class MockGameObjectFactory : public IGameObjectFactory{
public:
    MockGameObjectFactory(GameObjectHandle& gameObject);
    virtual GameObjectHandle Create();

private:
    GameObjectHandle gameObject;
};
}