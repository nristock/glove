#include "MockGameObjectFactory.hpp"

namespace glove {
MockGameObjectFactory::MockGameObjectFactory(GameObjectHandle& gameObject) : gameObject(gameObject) {}

GameObjectHandle MockGameObjectFactory::Create() {
    return gameObject;
}
}