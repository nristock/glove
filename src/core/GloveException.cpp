#include "GloveException.h"

#include <boost/format.hpp>

namespace glove {

GloveException::GloveException(std::string message) : message(message) {

}

GloveException::GloveException(std::string message, const char* file, int line) : message(message), file(file), line(line) {

}

GloveException::~GloveException() {
}

const char* GloveException::what() const throw () {
	return (boost::format("%1%\n\tin %2%:%3%") % message % file % line).str().c_str();
}

} /* namespace glove */
