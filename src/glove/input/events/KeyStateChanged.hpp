#pragma once

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {
class KeyStateChanged {
  public:
    KeyStateChanged(float keyValue) : keyValue(keyValue) {
    }

    KeyStateChanged(bool isDown) : keyValue(isDown ? 0.0f : 1.0f) {
    }

    float GetAxisValue() const {
        return keyValue;
    }

    bool IsKeyDown() const {
        return keyValue == 0.0f;
    }

    bool IsKeyUp() const {
        return keyValue == 1.0f;
    }

  private:
    const float keyValue;
};
}