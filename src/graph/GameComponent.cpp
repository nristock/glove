#include "GameComponent.h"

#include "core/GloveFwd.h"

namespace glove {

GameComponent::GameComponent() : EnableProfilable() {

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