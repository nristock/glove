#include "EmptyGameObjectFactory.h"

#include "graph/gameobject/GameObject.h"

namespace glove {

GameObjectHandle EmptyGameObjectFactory::Create() {
    return std::make_shared<GameObject>();
}
}