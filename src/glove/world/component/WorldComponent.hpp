#pragma once

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {

/**
* A WorldComponent can only be attached to a World directly and doesn't have a transform.
*
* These components can be used to update any whole-world logic (e.g. weather, time).
*/
class BD_API_EXPORT WorldComponent {
  public:
    virtual ~WorldComponent() = default;

    /// Advances the simulation by @p time seconds.
    virtual void Tick(double time) = 0;
};

} /* namespace BlueDwarf */