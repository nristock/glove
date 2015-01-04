#pragma once

#include "graph/Graph.h"
#include "graph/gameobject/factories/IGameObjectFactory.h"

namespace glove {

class EmptyGameObjectFactory : public IGameObjectFactory {
public:
    virtual GameObjectHandle Create();
};

}