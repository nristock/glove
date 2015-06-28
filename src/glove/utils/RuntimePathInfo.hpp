#pragma once

#include <string>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {
void BD_API_EXPORT GetExecutionPathInfo(std::string& executablePath, std::string& executableName);
}