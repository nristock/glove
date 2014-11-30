#pragma once

#include <vendor/gmock/gmock.h>
#include <core/graph/GameObject.h>
#include <core/pitamem/MemoryProfile.h>

namespace glove {

class GameObjectMock : public GameObject {
	Profilable()
public:
	GameObjectMock() : EnableProfilable() {  };

    MOCK_METHOD0(Init, void());
};

} /* namespace glove */