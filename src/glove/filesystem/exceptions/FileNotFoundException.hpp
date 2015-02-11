#pragma once

#include "glove/GloveException.hpp"
#include "glove/filesystem/io/File.hpp"

namespace glove {

class GLOVE_API_EXPORT FileNotFoundException : public GloveException {
public:
    FileNotFoundException(const File& file, char const* source, int line);
};

} /* namespace glove */