#include "Scenegraph.h"
#include <core/graph/GameObject.h>
#include <core/graph/Camera.h>

namespace glove {

Scenegraph::Scenegraph() :
	EnableProfilable() {


}

Scenegraph::~Scenegraph() {
    for (auto gameObject : gameObjects) {
        gameObject->Destroy();
    }
}

GameObjectPointer Scenegraph::CreateSimpleGameObject() {
    return CreateGameObject<GameObject>([this]() {
		return new GameObject();
    });
}

CameraPointer Scenegraph::CreateCamera() {
    auto cam = CameraPointer(new Camera());
    cam->Init();

    return cam;
}

void Scenegraph::Update() {
    for (auto gameObject : gameObjects) {
        gameObject->Update();
    }
}

void Scenegraph::IterateGameObjects(std::function<void(GameObjectPointer)> callback) {
    for (auto gameObject : gameObjects) {
        callback(gameObject);
    }
}

void Scenegraph::InjectGameObject(GameObjectPointer gameObject) {
    gameObjects.push_back(gameObject);
}

void Scenegraph::SetActiveCamera(CameraPointer camera) {
    mainCamera = camera;
}

} /* namespace glove */