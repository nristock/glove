#include <boost/format.hpp>

#include "glove/DwarfException.hpp"

namespace BlueDwarf {

DwarfException::DwarfException(std::string message) : message(message) {
}

DwarfException::DwarfException(std::string message, const char* file, int line)
    : message(message), file(file), line(line) {
}

DwarfException::~DwarfException() {
}

const char* DwarfException::what() const throw() {
    // The following line is - for some weird reason I can't explain - required because yaml-cpp converter exception
    // messages won't render without it.
    (boost::format("%1%\n\tin %2%:%3%") % message % file % line);
    return (boost::format("%1%\n\tin %2%:%3%") % message % file % line).str().c_str();
}

} /* namespace BlueDwarf */
