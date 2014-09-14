#include "Scenegraph.h"
#include "GameObject.h"
#include "rendering/Camera.h"

namespace glove {

Scenegraph::Scenegraph() {
	// TODO Auto-generated constructor stub

}

Scenegraph::~Scenegraph() {
	for (auto gameObject : gameObjects) {
		gameObject->Destroy();
	}
}

GameObjectPointer Scenegraph::CreateGameObject() {
	return CreateGameObject<GameObject>([]() {return new GameObject(); });
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

template<class T> std::shared_ptr<T> Scenegraph::CreateGameObject(std::function<T*()> allocator) {
	return CreateGameObject<T>(allocator, [](std::shared_ptr<T> object){}, [](std::shared_ptr<T> object){});
}

template<class T> std::shared_ptr<T> Scenegraph::CreateGameObject(std::function<T*()> allocator, std::function<void(std::shared_ptr<T>)> preInit) {
	return CreateGameObject<T>(allocator, preInit, [](std::shared_ptr<T> object){});
}

template<class T> std::shared_ptr<T> Scenegraph::CreateGameObject(std::function<T*()> allocator, std::function<void(std::shared_ptr<T>)> preInit, std::function<void(std::shared_ptr<T>)> postInit) {
	auto go = GameObjectPointer(allocator());

	preInit(go);
	go->Init();
	postInit(go);

	gameObjects.push_back(go);

	return go;
}

void Scenegraph::InjectGameObject(GameObjectPointer gameObject) {
	gameObjects.push_back(gameObject);
}

void Scenegraph::SetActiveCamera(CameraPointer camera)  {
	mainCamera = camera;
}

} /* namespace glove */
