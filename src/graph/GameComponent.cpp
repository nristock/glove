#include "GameComponent.h"

#include "core/GloveFwd.h"

namespace glove {
	
GameComponent::GameComponent(GameObjectPtr parent) : parent(parent) {

}

GameComponent::~GameComponent() {
	
}

} // namespace glove