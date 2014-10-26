#pragma once

#include <list>
#include <functional>
#include <memory>

#include <glm/glm.hpp>

#include "core/GloveFwd.h"
#include "graph/GameObject.h"

namespace glove {

class GameObject;

class Scenegraph {
Profilable();
public:
	Scenegraph();

    virtual ~Scenegraph();

    virtual GameObjectPointer CreateSimpleGameObject();

    template<class T>
    std::shared_ptr<T> CreateGameObject(std::function<T*()> allocator) {
        return CreateGameObject<T>(allocator, [](std::shared_ptr<T> object) {
        }, [](std::shared_ptr<T> object) {
        });
    }

    template<class T>
    std::shared_ptr<T> CreateGameObject(std::function<T*()> allocator, std::function<void(std::shared_ptr<T>)> preInit) {
        return CreateGameObject<T>(allocator, preInit, [](std::shared_ptr<T> object) {
        });
    }

    template<class T>
    std::shared_ptr<T> CreateGameObject(std::function<T*()> allocator, std::function<void(std::shared_ptr<T>)> preInit, std::function<void(std::shared_ptr<T>)> postInit) {
        typedef std::shared_ptr<T> SharedPtrType;

        SharedPtrType go = SharedPtrType(allocator());

        preInit(go);
        go->Init();
        postInit(go);

        gameObjects.push_back(go);

        return go;
    }

    virtual void InjectGameObject(GameObjectPointer gameObject);

    virtual CameraPointer CreateCamera();

    void Update();

    virtual void IterateGameObjects(std::function<void(GameObjectPointer)> callback);

    virtual void SetActiveCamera(CameraPointer camera);

    virtual CameraPointer GetMainCamera() const {
        return mainCamera;
    }

    size_t GetGameObjectCount() const {
        return gameObjects.size();
    }

protected:
    std::list<GameObjectPointer> gameObjects;

    CameraPointer mainCamera;
};

} /* namespace glove */
