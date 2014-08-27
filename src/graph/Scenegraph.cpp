/*
 * Scenegraph.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: monofraps
 */

#include "Scenegraph.h"
#include "GameObject.h"

namespace glove {

Scenegraph::Scenegraph() {
	// TODO Auto-generated constructor stub

}

Scenegraph::~Scenegraph() {
	for (auto it = this->gameObjects.begin();
			it != this->gameObjects.end(); ++it) {
		delete (*it);
	}
}

GameObject* Scenegraph::CreateGameObject() {
	auto go = new GameObject();
	this->gameObjects.push_back(go);

	return go;
}

void Scenegraph::Update() {
	for (auto it = this->gameObjects.begin();
			it != this->gameObjects.end(); ++it) {

	}
}

} /* namespace glove */
