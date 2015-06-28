#pragma once

#include "glove/DwarfException.hpp"

namespace BlueDwarf {

class BD_API_EXPORT StreamErrorException : public DwarfException {

public:
    StreamErrorException(std::string message, char const* file, int line);
};

} /* namespace BlueDwarf */