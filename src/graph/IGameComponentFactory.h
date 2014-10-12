#pragma once

#include <list>
#include <memory>

#include <glm/glm.hpp>

#include "core/GloveFwd.h"
#include "memory/GloveMemory.h"

namespace glove {

class IGameComponentFactory {
	GLOVE_MEM_ALLOC_FUNCS("IGameComponentFactory")
public:
	IGameComponentFactory();
	virtual ~IGameComponentFactory();

	virtual GameComponentPtr Build(const GameObjectPtr owner) const = 0;
};

} /* namespace glove */
