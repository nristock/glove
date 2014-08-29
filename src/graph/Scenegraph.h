/*
 * Scenegraph.h
 *
 *  Created on: Jul 21, 2014
 *      Author: monofraps
 */

#ifndef SCENEGRAPH_H_
#define SCENEGRAPH_H_

#include <list>

#include "core/GloveObject.h"

namespace glove {

class GameObject;

class Scenegraph : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("Scenegraph");
public:
	Scenegraph();
	virtual ~Scenegraph();

	GameObject* CreateGameObject();

	void Update();

private:
	std::list<GameObject*> gameObjects;
};

} /* namespace glove */

#endif /* SCENEGRAPH_H_ */
