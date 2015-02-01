#pragma once

#include "core/GloveException.h"
#include "core/filesystem/io/File.hpp"

namespace glove {

class FileInfoQueryException : public GloveException {
public:
    FileInfoQueryException(const Path& path, const std::string& message, char const* source, int line);
};

} /* namespace glove */