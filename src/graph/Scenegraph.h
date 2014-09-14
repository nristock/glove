#ifndef SCENEGRAPH_H_
#define SCENEGRAPH_H_

#include <list>
#include <functional>
#include <memory>

#include <glm/glm.hpp>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

class GameObject;

class Scenegraph : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("Scenegraph");
public:
	Scenegraph();
	virtual ~Scenegraph();

	GameObjectPointer CreateGameObject();
	template<class T> std::shared_ptr<T> CreateGameObject(std::function<T*()> allocator);
	template<class T> std::shared_ptr<T> CreateGameObject(std::function<T*()> allocator, std::function<void(std::shared_ptr<T>)> preInit);
	template<class T> std::shared_ptr<T> CreateGameObject(std::function<T*()> allocator, std::function<void(std::shared_ptr<T>)> preInit, std::function<void(std::shared_ptr<T>)> postInit);

	void InjectGameObject(GameObjectPointer gameObject);

	CameraPointer CreateCamera();

	void Update();

	void IterateGameObjects(std::function<void(GameObjectPointer)> callback);
	void SetActiveCamera(CameraPointer camera);

	CameraPointer GetMainCamera() const { return mainCamera; }

private:
	std::list<GameObjectPointer> gameObjects;
	
	CameraPointer mainCamera;
};

} /* namespace glove */

#endif /* SCENEGRAPH_H_ */
