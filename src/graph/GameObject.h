/*
 * GameObject.h
 *
 *  Created on: Jul 21, 2014
 *      Author: monofraps
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <list>
#include <memory>

#include <glm/glm.hpp>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

#include "graph/Transform.h"

namespace glove {

class GameObject : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GameObject")
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init() {};
	virtual void Destroy() {};

	virtual void Update() {};
	
	/*!
	 * Adds a component to the game object. 
	 * The game object takes complete ownership of the component. The component must not be deleted manually.
	 */
	virtual void AddComponent(GameComponent* component);

	/*!
	 * Returns a pointer to the first component found. The game object stays the exclusive owner of the component.
	 * A user may store the returned weak_ptr for optimization purposes.
	 */
	template<class T> std::weak_ptr<T> GetComponent();

	/*!
	 * Iterates all attached components and calls the specified callback.
	 */
	virtual void IterateComponents(std::function<void(GameComponentPointer)> callback);

	virtual void IterateRenderableComponents(std::function<void(IRenderablePointer)> callback);

protected:
	std::list<GameComponentPointer> components;
	std::list <std::weak_ptr<IRenderable>> renderableComponents;

	Transform transform;
};

} /* namespace glove */

#endif /* GAMEOBJECT_H_ */
