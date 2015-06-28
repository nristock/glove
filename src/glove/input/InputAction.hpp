#pragma once

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {
class BD_API_EXPORT InputAction {
  public:
    virtual ~InputAction() = default;

    virtual void Execute() = 0;
};
}