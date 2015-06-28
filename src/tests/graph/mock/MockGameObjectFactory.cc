#include "MockGameObjectFactory.hpp"

namespace BlueDwarf {
MockGameObjectFactory::MockGameObjectFactory(GameObjectHandle& gameObject) : gameObject(gameObject) {}

GameObjectHandle MockGameObjectFactory::Create() {
    return gameObject;
}
}