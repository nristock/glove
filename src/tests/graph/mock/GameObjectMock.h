#pragma once

#include <vendor/gmock/gmock.h>
#include <glove/graph/gameobject/GameObject.h>

namespace glove {

class GameObjectMock : public GameObject {
public:
	GameObjectMock() = default;

    MOCK_METHOD0(Init, void());
};

} /* namespace glove */