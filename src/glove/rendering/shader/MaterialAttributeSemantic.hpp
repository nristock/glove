#pragma once

#include <ostream>

#include "glove/GloveApi.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
enum class GLOVE_API_EXPORT MaterialAttributeSemantic {
    MVP_MAT
};

std::ostream& operator<< (std::ostream& os, MaterialAttributeSemantic attributeSemantic);

} // namespace glove