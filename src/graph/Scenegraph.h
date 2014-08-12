/*
 * Scenegraph.h
 *
 *  Created on: Jul 21, 2014
 *      Author: monofraps
 */

#ifndef SCENEGRAPH_H_
#define SCENEGRAPH_H_

#include <list>

namespace oglt {
namespace scenegraph {

class GameObject;

class Scenegraph {
public:
	Scenegraph();
	virtual ~Scenegraph();

	GameObject* CreateGameObject();

	void Update();

private:
	std::list<GameObject*> gameObjects;
};

} /* namespace scenegraph */
} /* namespace oglt */

#endif /* SCENEGRAPH_H_ */
