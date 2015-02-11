#pragma once

#include "glove/graph/Graph.hpp"

namespace glove {

class IGameObjectFactory {
public:
    virtual ~IGameObjectFactory() = default;

    virtual GameObjectHandle Create() = 0;
};

}