#pragma once

#include <memory>

namespace BlueDwarf {

class InputAction;
using InputActionHandle = std::shared_ptr<InputAction>;

} /* namespace BlueDwarf */

#if !defined(BD_INPUT_FWD_ONLY)
#include "glove/input/Keys.hpp"
#include "glove/input/InputAction.hpp"
#include "glove/input/InputActionRegistry.hpp"
#endif