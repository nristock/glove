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

	virtual GameObjectPointer CreateSimpleGameObject();
	template<class T> std::shared_ptr<T> CreateGameObject(std::function<T*()> allocator);
	template<class T> std::shared_ptr<T> CreateGameObject(std::function<T*()> allocator, std::function<void(std::shared_ptr<T>)> preInit);
	template<class T> std::shared_ptr<T> CreateGameObject(std::function<T*()> allocator, std::function<void(std::shared_ptr<T>)> preInit, std::function<void(std::shared_ptr<T>)> postInit);

	virtual void InjectGameObject(GameObjectPointer gameObject);

	virtual CameraPointer CreateCamera();

	void Update();

	virtual void IterateGameObjects(std::function<void(GameObjectPointer)> callback);
	virtual void SetActiveCamera(CameraPointer camera);

	virtual CameraPointer GetMainCamera() const { return mainCamera; }

protected:
	std::list<GameObjectPointer> gameObjects;
	
	CameraPointer mainCamera;
};

} /* namespace glove */

#endif /* SCENEGRAPH_H_ */
