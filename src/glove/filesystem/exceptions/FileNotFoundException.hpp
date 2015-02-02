#pragma once

#include "glove/GloveException.h"
#include "glove/filesystem/io/File.hpp"

namespace glove {

class FileNotFoundException : public GloveException {
public:
    FileNotFoundException(const File& file, char const* source, int line);
};

} /* namespace glove */