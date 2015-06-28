#pragma once

#include <gmock/gmock.hpp>

#include <glove/world/component/EntityComponent.hpp>

namespace BlueDwarf {
class EntityComponentMock : public EntityComponent {
  public:
    MOCK_METHOD1(Tick, void(double time));
    MOCK_METHOD0(CreateSceneProxy, SceneProxyHandle());
};

} /* namespace BlueDwarf */