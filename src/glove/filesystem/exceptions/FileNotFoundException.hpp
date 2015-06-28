#pragma once

#include "glove/DwarfException.hpp"
#include "glove/filesystem/io/File.hpp"

namespace BlueDwarf {

class BD_API_EXPORT FileNotFoundException : public DwarfException {
public:
    FileNotFoundException(const File& file, char const* source, int line);
};

} /* namespace BlueDwarf */