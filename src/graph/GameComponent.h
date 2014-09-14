#ifndef GRAPH_GAMECOMPONENT_H_
#define GRAPH_GAMECOMPONENT_H_

#include "core/GloveObject.h"

namespace glove {

class GameComponent : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GameComponent")
public:
	GameComponent();
	virtual ~GameComponent();
};


} // namespace glove

#endif