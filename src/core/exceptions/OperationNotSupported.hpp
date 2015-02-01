#pragma once

#include <boost/format.hpp>

#include <core/GloveException.h>

namespace glove {
class OperationNotSupportedException : public GloveException {
  public:
    OperationNotSupportedException(const std::string& operationName, const std::string& implementationName,
                                   char const* file, int line)
        : GloveException((boost::format("%1% is not supported by its implementation: %2%") % operationName %
                          implementationName).str(),
                         file, line) {}
};
}