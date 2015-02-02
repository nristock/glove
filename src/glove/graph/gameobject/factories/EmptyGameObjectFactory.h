#pragma once

#include "glove/graph/Graph.h"
#include "glove/graph/gameobject/factories/IGameObjectFactory.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class EmptyGameObjectFactory : public IGameObjectFactory {
public:
    virtual GameObjectHandle Create();

    static GameObjectHandle CreateEmpty();
};

}