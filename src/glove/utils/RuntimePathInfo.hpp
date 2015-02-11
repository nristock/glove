#pragma once

#include <string>

#include "glove/GloveApi.hpp"

namespace glove {
void GLOVE_API_EXPORT GetExecutionPathInfo(std::string& executablePath, std::string& executableName);
}