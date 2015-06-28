#pragma once

#include "glove/DwarfException.hpp"

namespace BlueDwarf {

class BD_API_EXPORT InvalidFileTypeException : public DwarfException {

public:
    InvalidFileTypeException(std::string& message, char const* file, int line);
};

} /* namespace BlueDwarf */