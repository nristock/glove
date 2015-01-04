#pragma once

#include <vendor/gmock/gmock.h>
#include <core/pitamem/MemoryProfile.h>

namespace glove {

class GameObjectMock : public GameObject {
public:
    MOCK_METHOD0(Init, void());
};

} /* namespace glove */