#pragma once

#include <list>
#include <memory>
#include <map>
#include <mutex>

#include <glm/glm.hpp>

#include "glove/GloveFwd.hpp"
#include "glove/graph/Graph.hpp"
#include "glove/graph/Transform.hpp"
#include "glove/graph/GraphNode.hpp"
#include "glove/utils/TypeInfo.hpp"
#include "glove/utils/IsA.hpp"
#include "glove/utils/BitMask.hpp"

namespace glove {

class GLOVE_API_EXPORT GameObject : public GraphNode {
  public:
    virtual ~GameObject();

    virtual void Init() {}
    virtual void Destroy() {}
    virtual void Update() {}

    /**
    * Adds a component to the game object.
    */
    virtual void AddComponent(const SharedGameComponentHandle& component);

    /**
    * Returns a pointer to the first component found.
    * A user may store the returned weak_ptr for optimization purposes.
    */
    template <class T> std::weak_ptr<T> GetComponent();

    /**
    * Iterates all attached components and calls the specified callback.
    */
    virtual void IterateComponents(std::function<void(const GameComponentHandle&)> callback);

    LayerMask GetLayer() const;

  protected:
    typedef std::lock_guard<std::mutex> Lock;
    typedef std::multimap<TypeInfoRef, GameComponentHandle, TypeInfoComparator> ComponentIndex;
    typedef std::pair<TypeInfoRef, GameComponentHandle> ComponentIndexEntry;
    typedef std::pair<ComponentIndex::iterator, ComponentIndex::iterator> ComponentIndexRange;

    template <class T> void IndexComponentsOfType() {
        for (const SharedGameComponentHandle& handle : components) {
            if (IsA<T>(handle)) {
                componentIndex.insert(ComponentIndexEntry(typeid(T), handle));
            }
        }
    }

    void IndexSingleComponent(const SharedGameComponentHandle& gameComponent);

    std::mutex componentListSemaphore;
    std::mutex componentIndexSemaphore;
    std::list<SharedGameComponentHandle> components;
    ComponentIndex componentIndex;
    LayerMask layer;
};

} /* namespace glove */