#include "glove/graph/gameobject/GameObject.hpp"
#include "glove/graph/gamecomponent/GameComponent.hpp"

namespace glove {

GameObject::~GameObject() {
    componentIndex.clear();
    components.clear();
}

void GameObject::AddComponent(const SharedGameComponentHandle& component) {
    component->OnAttach(std::dynamic_pointer_cast<GameObject>(shared_from_this()));
    components.push_back(component);

    Lock indexLock(componentIndexSemaphore);
    IndexSingleComponent(component);
}

template <class T> std::weak_ptr<T> GameObject::GetComponent() {
    Lock indexLock(componentIndexSemaphore);

    if(componentIndex.count(typeid(T)) == 0) {
        Lock listLock(componentListSemaphore);
        IndexComponentsOfType<T>();
        if(componentIndex.count(typeid(T)) == 0) {
            // TODO: throw
        }
    }

    //TODO: return list
    const ComponentIndexRange indexRange = componentIndex.equal_range(typeid(T));
    return std::weak_ptr<T>(std::dynamic_pointer_cast<T>(indexRange.first->second));
}

void GameObject::IterateComponents(std::function<void(const GameComponentHandle&)> callback) {
    Lock lock(componentListSemaphore);

    for (auto component : components) {
        callback(component);
    }
}

void GameObject::IndexSingleComponent(const SharedGameComponentHandle& gameComponent) {
//    if(IsA<IRenderable>(gameComponent)) {
//        componentIndex.insert(ComponentIndexEntry(typeid(IRenderable), gameComponent));
//    }
}

LayerMask GameObject::GetLayer() const {
    return layer;
}
} /* namespace glove */
