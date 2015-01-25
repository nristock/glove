#pragma once

#include <ostream>

namespace glove {

/// @ingroup RenderSubsystemInterface
enum class MaterialAttributeSemantic {
    MVP_MAT
};

std::ostream& operator<< (std::ostream& os, MaterialAttributeSemantic attributeSemantic);

} // namespace glove