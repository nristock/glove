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
#include "graph/IGraphNode.h"

namespace glove {

class GameObject : public GloveObject, public IGraphNode, public std::enable_shared_from_this<GameObject> {
	GLOVE_MEM_ALLOC_FUNCS("GameObject")
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init() {};
	virtual void Destroy() {};

	virtual void Update() {};

	virtual void AttachChild(IGraphNodePtr child);
	virtual void RemoveChild(IGraphNodePtr child);
	
	/*!
	 * Adds a component to the game object. 
	 * The game object takes complete ownership of the component. The component must not be deleted manually.
	 */
	virtual void AddComponent(GameComponentPtr component);
	
	// Using auto_ptr here because boost::python doesn't support unique_ptr yet
	virtual void AddUniqueComponent(std::auto_ptr<GameComponent> component);

	virtual std::weak_ptr<GameComponent> CreateComponent(const IGameComponentFactory& factory);

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
	
	virtual void OnParented(IGraphNodePtr parent);
};

} /* namespace glove */

#endif /* GAMEOBJECT_H_ */
