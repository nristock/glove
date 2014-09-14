#include "PyCoreComponents.h"

#include <string>

#include <boost/python.hpp>

#include "log/Log.h"

namespace glove {
namespace python {

void LogWrap(const std::string& text) {
	// Don't log new-line strings
	if (text.find_first_not_of('\n') != std::string::npos) {
		LOG(logging::globalLogger, info, "Python Out: " << text);
	}
}

void ExportCoreComponents() {
	boost::python::def("Log", &LogWrap);
}

} // namespace python
} // namespace glove