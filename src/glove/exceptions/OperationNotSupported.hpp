#pragma once

#include <boost/format.hpp>

#include "glove/DwarfException.hpp"

namespace BlueDwarf {
class BD_API_EXPORT OperationNotSupportedException : public DwarfException {
  public:
    OperationNotSupportedException(const std::string& operationName, const std::string& implementationName,
                                   char const* file, int line);
};
}