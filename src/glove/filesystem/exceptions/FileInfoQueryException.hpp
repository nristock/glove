#pragma once

#include "glove/GloveException.hpp"
#include "glove/filesystem/Path.hpp"

namespace glove {

class FileInfoQueryException : public GloveException {
public:
    FileInfoQueryException(const Path& path, const std::string& message, char const* source, int line);
};

} /* namespace glove */