#pragma once

#include <core/GloveFwd.h>

namespace glove {

class IGameObjectFactory {
public:
    virtual ~IGameObjectFactory() = default;

    virtual GameObjectHandle Create() = 0;
};

}