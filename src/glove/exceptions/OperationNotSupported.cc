#include "glove/exceptions/OperationNotSupported.hpp"

namespace BlueDwarf {

OperationNotSupportedException::OperationNotSupportedException(const std::string& operationName,
                                                               const std::string& implementationName, char const* file,
                                                               int line)
    : DwarfException(
          (boost::format("%1% is not supported by its implementation: %2%") % operationName % implementationName).str(),
          file, line) {
}
}