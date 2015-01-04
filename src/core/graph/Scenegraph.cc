#include "Scenegraph.h"
#include "gameobject/factories/IGameObjectFactory.h"
#include "gameobject/factories/EmptyGameObjectFactory.h"

namespace glove {

Scenegraph::Scenegraph() {
}

Scenegraph::~Scenegraph() {
    for (auto gameObject : gameObjects) {
        gameObject->Destroy();
    }
}

GameObjectHandle Scenegraph::CreateSimpleGameObject() {
    EmptyGameObjectFactory defaultGameObjectFactory;
    return CreateGameObject(defaultGameObjectFactory);
}

void Scenegraph::IterateGameObjects(GameObjectIterationCallback callback) {
    for (auto gameObject : gameObjects) {
        callback(gameObject);
    }
}

void Scenegraph::InjectGameObject(const GameObjectHandle& gameObject) {
    gameObjects.push_back(gameObject);
}

void Scenegraph::IterateGameObjects(GameObjectIterationCallback callback, GameObjectPredicate predicate) {
    for(auto& gameObject : gameObjects) {
        if(predicate(gameObject)) {
            callback(gameObject);
        }
    }
}

GameObjectHandle Scenegraph::CreateGameObject(IGameObjectFactory& gameObjectFactory, GameObjectPreInitCallback preInit) {
    return CreateGameObject(gameObjectFactory, preInit, [](const GameObjectHandle& object) {});
}

GameObjectHandle Scenegraph::CreateGameObject(IGameObjectFactory& gameObjectFactory) {
    return CreateGameObject(gameObjectFactory, [](const GameObjectHandle& object) {}, [](const GameObjectHandle& object) {});
}

GameObjectHandle Scenegraph::CreateGameObject(IGameObjectFactory& gameObjectFactory, GameObjectPreInitCallback preInit, GameObjectPostInitCallback postInit) {
    GameObjectHandle gameObject = gameObjectFactory.Create();
    preInit(gameObject);
    gameObject->Init();
    postInit(gameObject);

    gameObjects.push_back(gameObject);

    return gameObject;
}

GameObjectHandle Scenegraph::CreateGameObject(const GameObjectFactoryHandle& gameObjectFactory) {
    return CreateGameObject(*gameObjectFactory);
}

GameObjectHandle Scenegraph::CreateGameObject(const GameObjectFactoryHandle& gameObjectFactory, GameObjectPreInitCallback preInit) {
    return CreateGameObject(*gameObjectFactory, preInit);
}

GameObjectHandle Scenegraph::CreateGameObject(const GameObjectFactoryHandle& gameObjectFactory, GameObjectPreInitCallback preInit, GameObjectPostInitCallback postInit) {
    return CreateGameObject(*gameObjectFactory, preInit, postInit);
}
} /* namespace glove */
