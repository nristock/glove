#pragma once

#include <memory>

namespace glove {

class InputAction;
using InputActionHandle = std::shared_ptr<InputAction>

} /* namespace glove */

#if !defined(GLOVE_INPUT_FWD_ONLY)
#include "glove/input/Keys.hpp"
#include "glove/input/InputAction.hpp"
#include "glove/input/InputActionRegistry.hpp"
#endif