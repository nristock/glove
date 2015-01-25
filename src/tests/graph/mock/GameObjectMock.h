#pragma once

#include <vendor/gmock/gmock.h>
#include <core/graph/gameobject/GameObject.h>
#include <core/pitamem/MemoryProfile.h>

namespace glove {

class GameObjectMock : public GameObject {
public:
	GameObjectMock() = default;

    MOCK_METHOD0(Init, void());
};

} /* namespace glove */