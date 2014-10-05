#include "GameComponent.h"

#include "core/GloveFwd.h"

namespace glove {
	
GameComponent::GameComponent() {

}

GameComponent::~GameComponent() {
	
}

void GameComponent::OnAttach(GameObjectPtr owner) {
	this->owner = owner;
}

void GameComponent::OnDetach() {
	owner.reset();
}

} // namespace glove