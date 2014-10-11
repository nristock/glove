#pragma once

#include "tests/gmock/gmock.h"
#include "graph/GameObject.h"

namespace glove {

class GameObjectMock : public GameObject {
public:
    MOCK_METHOD0(Init, void());
};

} /* namespace glove */