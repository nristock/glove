#include "GameComponent.h"

namespace glove {

void GameComponent::OnAttach(const GameObjectHandle& owner) {
    this->owner = owner;
}

void GameComponent::OnDetach() {
    owner.reset();
}

} // namespace glove