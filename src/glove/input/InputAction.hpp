#pragma once

#include "glove/GloveApi.hpp"

namespace glove {
class GLOVE_API_EXPORT InputAction {
  public:
    virtual ~InputAction() = default;

    virtual void Execute() = 0;
};
}