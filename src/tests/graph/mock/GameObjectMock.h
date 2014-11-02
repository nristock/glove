#pragma once

#include <vendor/gmock/gmock.h>
#include "graph/GameObject.h"

namespace glove {

class GameObjectMock : public GameObject {
	Profilable()
public:
	GameObjectMock() : EnableProfilable() {  };

    MOCK_METHOD0(Init, void());
};

} /* namespace glove */