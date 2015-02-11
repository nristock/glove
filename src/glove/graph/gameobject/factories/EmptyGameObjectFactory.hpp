#pragma once

#include "glove/graph/Graph.hpp"
#include "glove/graph/gameobject/factories/IGameObjectFactory.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT EmptyGameObjectFactory : public IGameObjectFactory {
public:
    virtual GameObjectHandle Create();

    static GameObjectHandle CreateEmpty();
};

}