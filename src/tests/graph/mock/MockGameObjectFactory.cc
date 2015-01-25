#include "MockGameObjectFactory.h"

namespace glove {
MockGameObjectFactory::MockGameObjectFactory(GameObjectHandle& gameObject) : gameObject(gameObject) {}

GameObjectHandle MockGameObjectFactory::Create() {
    return gameObject;
}
}