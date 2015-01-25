#pragma once

#include <list>
#include <functional>
#include <memory>

#include <glm/glm.hpp>

#include "GloveFwd.h"
#include "graph/Graph.h"
#include "graph/gameobject/GameObject.h"
#include "utils/BitMask.h"

namespace glove {

typedef std::function<void(const GameObjectHandle&)> GameObjectIterationCallback;
typedef std::function<bool(const GameObjectHandle&)> GameObjectPredicate;
typedef std::function<void(const GameObjectHandle&)> GameObjectPreInitCallback;
typedef std::function<void(const GameObjectHandle&)> GameObjectPostInitCallback;

class Scenegraph {
  public:
    struct LayerPredicate {
        static GameObjectPredicate IsOnLayer(LayerMask layerMask) {
            return
                [layerMask](const GameObjectHandle& gameObject) { return gameObject->GetLayer().Contains(layerMask); };
        }

        static GameObjectPredicate IsNotOnLayer(LayerMask layerMask) {
            return
                [layerMask](const GameObjectHandle& gameObject) { return !gameObject->GetLayer().Contains(layerMask); };
        }
    };

    Scenegraph();
    virtual ~Scenegraph();

    virtual GameObjectHandle CreateSimpleGameObject();

    virtual GameObjectHandle CreateGameObject(IGameObjectFactory& gameObjectFactory);
    virtual GameObjectHandle CreateGameObject(const GameObjectFactoryHandle& gameObjectFactory);

    virtual GameObjectHandle CreateGameObject(IGameObjectFactory& gameObjectFactory, GameObjectPreInitCallback preInit);
    virtual GameObjectHandle CreateGameObject(const GameObjectFactoryHandle& gameObjectFactory,
                                              GameObjectPreInitCallback preInit);

    virtual GameObjectHandle CreateGameObject(IGameObjectFactory& gameObjectFactory, GameObjectPreInitCallback preInit,
                                              GameObjectPostInitCallback postInit);
    virtual GameObjectHandle CreateGameObject(const GameObjectFactoryHandle& gameObjectFactory,
                                              GameObjectPreInitCallback preInit, GameObjectPostInitCallback postInit);

    virtual void InjectGameObject(const GameObjectHandle& gameObject);

    virtual void IterateGameObjects(GameObjectIterationCallback callback);
    virtual void IterateGameObjects(GameObjectIterationCallback callback, GameObjectPredicate predicate);

    virtual size_t GetGameObjectCount() const { return gameObjects.size(); }

  protected:
    std::list<GameObjectHandle> gameObjects;
};

} /* namespace glove */
