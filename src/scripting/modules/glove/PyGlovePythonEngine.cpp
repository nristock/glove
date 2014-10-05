#include "PyGlovePythonEngine.h"

#include <boost/python.hpp>

#include "scripting/GlovePythonEngine.h"

namespace glove {
namespace python {

void ExportGlovePythonEngine() {
	boost::python::class_<glove::GlovePythonEngine, boost::python::bases<GloveObject>, std::shared_ptr<GlovePythonEngine>>("GlovePythonEngine");
}

} // namespace python
} // namespace glove