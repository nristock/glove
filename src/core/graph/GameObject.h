#pragma once

#include <list>
#include <memory>

#include <glm/glm.hpp>

#include "core/GloveFwd.h"

#include <pitamem/MemoryProfile.h>
#include <graph/Transform.h>
#include <graph/IGraphNode.h>

namespace glove {

class GameObject : public IGraphNode, public std::enable_shared_from_this<GameObject> {
Profilable();
public:
	GameObject();

    virtual ~GameObject();

    virtual void Init() {
    };

    virtual void Destroy() {
    };

    virtual void Update() {
    };

    virtual void AttachChild(IGraphNodePtr child);

    virtual void RemoveChild(IGraphNodePtr child);

    /**
    * Adds a component to the game object.
    * The game object takes complete ownership of the component. The component must not be deleted manually.
    */
    virtual void AddComponent(GameComponentPtr component);

    virtual std::weak_ptr<GameComponent> CreateComponent(const IGameComponentFactory& factory);

    /**
    * Returns a pointer to the first component found. The game object stays the exclusive owner of the component.
    * A user may store the returned weak_ptr for optimization purposes.
    */
    template<class T>
    std::weak_ptr<T> GetComponent();

    /**
    * Iterates all attached components and calls the specified callback.
    */
    virtual void IterateComponents(std::function<void(const GameComponentPointer&)> callback);

    virtual void IterateRenderableComponents(std::function<void(const IRenderablePointer&)> callback);

protected:
    std::list<GameComponentPointer> components;
    std::list<std::weak_ptr<IRenderable>> renderableComponents;

    virtual void OnParented(IGraphNodePtr parent);
};

} /* namespace glove */