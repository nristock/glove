#include "GameObject.h"

#include "GameComponent.h"
#include <core/rendering/IRenderable.h>

#include <core/graph/IGameComponentFactory.h>

namespace glove {

GameObject::~GameObject() {
    renderableComponents.clear();
    components.clear();
}

void GameObject::AddComponent(GameComponentPtr component) {
    component->OnAttach(shared_from_this());
    components.push_back(component);

    auto renderablePointer = std::dynamic_pointer_cast<IRenderable>(component);
    if (renderablePointer) {
        renderableComponents.push_back(std::weak_ptr<IRenderable>(renderablePointer));
    }
}

std::weak_ptr<GameComponent> GameObject::CreateComponent(const IGameComponentFactory& factory) {
    GameComponentPtr component = factory.Build(shared_from_this());

    components.push_back(component);
    auto renderablePointer = std::dynamic_pointer_cast<IRenderable>(component);
    if (renderablePointer) {
        renderableComponents.push_back(std::weak_ptr<IRenderable>(renderablePointer));
    }

    return std::weak_ptr<GameComponent>(component);
}

template <class T> std::weak_ptr<T> GameObject::GetComponent() {
    for (auto component : components) {
        if (typeid(*component) == typeid(T)) {
            return std::weak_ptr<T>(std::dynamic_pointer_cast<T>(component));
        }
    }
}

void GameObject::IterateComponents(std::function<void(const GameComponentPointer&)> callback) {
    for (auto component : components) {
        callback(component);
    }
}

void GameObject::IterateRenderableComponents(std::function<void(const IRenderablePtr&)> callback) {
    for (auto component : renderableComponents) {
        callback(component.lock());
    }
}

void GameObject::AttachChild(IGraphNodePtr child) {
    children.push_back(child);
    child->OnParented(shared_from_this());
}

void GameObject::RemoveChild(IGraphNodePtr child) {
    children.remove(child);
    child->OnParented(IGraphNodePtr());
}

void GameObject::OnParented(IGraphNodePtr parent) {
    this->parent = parent;

    transform.RecalculateMatrix();

    if (parent) {
        transform.RecalculateAccumulatedTransform(parent->GetTransform());
    } else {
        transform.RecalculateAccumulatedTransform(Transform::Identity());
    }
}

} /* namespace glove */
