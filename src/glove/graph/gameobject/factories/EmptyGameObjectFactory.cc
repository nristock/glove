#include "glove/graph/gameobject/factories/EmptyGameObjectFactory.hpp"
#include "glove/graph/gameobject/GameObject.hpp"

namespace glove {

GameObjectHandle EmptyGameObjectFactory::Create() {
    return EmptyGameObjectFactory::CreateEmpty();
}

GameObjectHandle EmptyGameObjectFactory::CreateEmpty() {
    return std::make_shared<GameObject>();
}
}