#pragma once

#include "glove/GloveApi.hpp"

namespace glove {

/**
* A WorldComponent can only be attached to a World directly and doesn't have a transform.
*
* These components can be used to update any whole-world logic (e.g. weather, time).
*/
class GLOVE_API_EXPORT WorldComponent {
  public:
    virtual ~WorldComponent() = default;

    /// Advances the simulation by @p time seconds.
    virtual void Tick(double time) = 0;
};

} /* namespace glove */