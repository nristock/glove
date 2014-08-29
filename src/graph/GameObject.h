/*
 * GameObject.h
 *
 *  Created on: Jul 21, 2014
 *      Author: monofraps
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "core/GloveObject.h"

namespace glove {

class GameObject : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GameObject")
public:
	GameObject();
	virtual ~GameObject();
};

} /* namespace glove */

#endif /* GAMEOBJECT_H_ */
