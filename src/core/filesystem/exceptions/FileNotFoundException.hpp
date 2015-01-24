#pragma once

#include "core/GloveException.h"
#include "core/filesystem/io/File.hpp"

namespace glove {

class FileNotFoundException : public GloveException {
public:
    FileNotFoundException(const File& file, char const* source, int line);
};

} /* namespace glove */