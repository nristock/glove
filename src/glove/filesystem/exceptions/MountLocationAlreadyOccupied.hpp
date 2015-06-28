#pragma once

#include "glove/filesystem/exceptions/MountError.hpp"
#include "glove/filesystem/Path.hpp"

namespace BlueDwarf {

class BD_API_EXPORT MountLocationAlreadyOccupied : public MountError {

public:
    MountLocationAlreadyOccupied(const Path& mountPath, char const* file, int line);
};

} /* namespace BlueDwarf */