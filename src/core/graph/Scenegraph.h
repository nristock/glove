#pragma once

#include <list>
#include <functional>
#include <memory>

#include <glm/glm.hpp>

#include "core/GloveFwd.h"
#include "graph/Graph.h"
#include "graph/gameobject/GameObject.h"

namespace glove {

typedef std::function<void(const GameObjectHandle&)> GameObjectIterationCallback;
typedef std::function<bool(const GameObjectHandle&)> GameObjectPredicate;
typedef std::function<void(const GameObjectHandle&)> GameObjectPreInitCallback;
typedef std::function<void(const GameObjectHandle&)> GameObjectPostInitCallback;

class Scenegraph {
  public:
    Scenegraph();
    virtual ~Scenegraph();

    virtual GameObjectHandle CreateSimpleGameObject();

    GameObjectHandle CreateGameObject(IGameObjectFactory& gameObjectFactory);
    GameObjectHandle CreateGameObject(const GameObjectFactoryHandle& gameObjectFactory);

    GameObjectHandle CreateGameObject(IGameObjectFactory& gameObjectFactory,
                                          GameObjectPreInitCallback preInit);
    GameObjectHandle CreateGameObject(const GameObjectFactoryHandle& gameObjectFactory,
                                      GameObjectPreInitCallback preInit);

    GameObjectHandle CreateGameObject(IGameObjectFactory& gameObjectFactory, GameObjectPreInitCallback preInit,
                                          GameObjectPostInitCallback postInit);
    GameObjectHandle CreateGameObject(const GameObjectFactoryHandle& gameObjectFactory, GameObjectPreInitCallback preInit,
                                      GameObjectPostInitCallback postInit);

    virtual void InjectGameObject(const GameObjectHandle& gameObject);

    virtual void IterateGameObjects(GameObjectIterationCallback callback);
    virtual void IterateGameObjects(GameObjectIterationCallback callback, GameObjectPredicate predicate);

    size_t GetGameObjectCount() const { return gameObjects.size(); }

  protected:
    std::list<GameObjectHandle> gameObjects;
};

} /* namespace glove */
