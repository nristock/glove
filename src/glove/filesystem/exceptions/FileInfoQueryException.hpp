#pragma once

#include "glove/DwarfException.hpp"
#include "glove/filesystem/Path.hpp"

namespace BlueDwarf {

class BD_API_EXPORT FileInfoQueryException : public DwarfException {
public:
    FileInfoQueryException(const Path& path, const std::string& message, char const* source, int line);
};

} /* namespace BlueDwarf */