#include "EmptyGameObjectFactory.h"

#include "glove/graph/gameobject/GameObject.h"

namespace glove {

GameObjectHandle EmptyGameObjectFactory::Create() {
    return EmptyGameObjectFactory::CreateEmpty();
}

GameObjectHandle EmptyGameObjectFactory::CreateEmpty() {
    return std::make_shared<GameObject>();
}
}