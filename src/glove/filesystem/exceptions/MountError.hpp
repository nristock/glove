#pragma once

#include "glove/DwarfException.hpp"
#include "glove/filesystem/Path.hpp"

namespace BlueDwarf {

class BD_API_EXPORT MountError : public DwarfException {

public:
    MountError(const std::string& message, char const* file, int line);
};

} /* namespace BlueDwarf */