#pragma once

#include <gmock/gmock.hpp>
#include <glove/graph/gameobject/GameObject.hpp>

namespace glove {

class GameObjectMock : public GameObject {
public:
	GameObjectMock() = default;

    MOCK_METHOD0(Init, void());
};

} /* namespace glove */