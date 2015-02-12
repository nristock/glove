#pragma once

#include "glove/filesystem/exceptions/MountError.hpp"
#include "glove/filesystem/Path.hpp"

namespace glove {

class GLOVE_API_EXPORT MountLocationAlreadyOccupied : public MountError {

public:
    MountLocationAlreadyOccupied(const Path& mountPath, char const* file, int line);
};

} /* namespace glove */