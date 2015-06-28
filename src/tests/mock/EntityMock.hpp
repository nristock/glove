#pragma once

#include <gmock/gmock.hpp>

#include <glove/world/entity/Entity.hpp>

namespace BlueDwarf {
class EntityMock : public Entity {
  public:
    EntityMock(const std::weak_ptr<World>& world) : Entity(world) { };

    MOCK_METHOD1(Tick, void(double time))
};

} /* namespace BlueDwarf */