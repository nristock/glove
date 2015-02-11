#pragma once

#include "glove/GloveApi.hpp"
#include "glove/graph/Graph.hpp"

namespace glove {

class GLOVE_API_EXPORT IGameObjectFactory {
public:
    virtual ~IGameObjectFactory() = default;

    virtual GameObjectHandle Create() = 0;
};

}