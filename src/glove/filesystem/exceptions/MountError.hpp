#pragma once

#include "glove/GloveException.hpp"
#include "glove/filesystem/Path.hpp"

namespace glove {

class GLOVE_API_EXPORT MountError : public GloveException {

public:
    MountError(const std::string& message, char const* file, int line);
};

} /* namespace glove */