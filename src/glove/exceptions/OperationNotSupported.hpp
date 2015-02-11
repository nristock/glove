#pragma once

#include <boost/format.hpp>

#include "glove/GloveException.hpp"

namespace glove {
class OperationNotSupportedException : public GloveException {
  public:
    OperationNotSupportedException(const std::string& operationName, const std::string& implementationName,
                                   char const* file, int line);
};
}