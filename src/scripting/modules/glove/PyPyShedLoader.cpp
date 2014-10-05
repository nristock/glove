#include "PyPyShedLoader.h"

#include <boost/python.hpp>

#include "scripting/GlovePythonEngine.h"
#include "shader/pyshed/PyShedLoader.h"

namespace glove {
namespace python {

void ExportPyShedLoader() {
	boost::python::class_<glove::PyShedLoader, boost::python::bases<GloveObject>, std::shared_ptr<PyShedLoader>>("PyShedLoader", boost::python::init<std::shared_ptr<GlovePythonEngine>>())
		.def("LoadPyshedShader", &PyShedLoader::LoadPysehdShader);
}

} // namespace python
} // namespace glove