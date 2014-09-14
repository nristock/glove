/*
 * GameObject.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: monofraps
 */

#include "GameObject.h"

#include "GameComponent.h"
#include "rendering/IRenderable.h"

namespace glove {

GameObject::GameObject() {
}

GameObject::~GameObject() {
	renderableComponents.clear();
	components.clear();
}

void GameObject::AddComponent(GameComponent* component) {
	GameComponentPointer componentPointer = GameComponentPtr(component);
	components.push_back(componentPointer);
	
	auto renderablePointer = std::dynamic_pointer_cast<IRenderable>(componentPointer);
	if (renderablePointer) {		
		renderableComponents.push_back(std::weak_ptr<IRenderable>(renderablePointer));
	}
}

template<class T> std::weak_ptr<T> GameObject::GetComponent() {
	for (auto component : components) {
		if (typeid(*component) == typeid(T)) {
			return std::weak_ptr<T>(std::dynamic_pointer_cast<T>(component));
		}
	}
}

void GameObject::IterateComponents(std::function<void(GameComponentPointer)> callback) {
	for (auto component : components) {
		callback(component);
	}
}

void GameObject::IterateRenderableComponents(std::function<void(IRenderablePointer)> callback) {
	for (auto component : renderableComponents) {
		callback(component.lock());
	}
}

} /* namespace glove */
