#ifndef GRAPH_GAMECOMPONENT_H_
#define GRAPH_GAMECOMPONENT_H_

#include "core/GloveObject.h"
#include "core/GloveFwd.h"

namespace glove {

class GameComponent : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GameComponent")
public:
	GameComponent(GameObjectPtr parent);
	virtual ~GameComponent();

protected:
	GameObjectPtr parent;
};


} // namespace glove

#endif