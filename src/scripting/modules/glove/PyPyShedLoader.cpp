#include "PyPyShedLoader.h"

#include <boost/python.hpp>

#include "scripting/GlovePythonEngine.h"
#include "shader/pyshed/PyShedLoader.h"

#include "scripting/PythonObjectFactory.h"

namespace glove {
namespace python {

void ExportPyShedLoader() {
	boost::python::class_<glove::PyShedLoader, std::shared_ptr<PyShedLoader>>("PyShedLoader", boost::python::no_init)
		.def("LoadPyshedShader", &PyShedLoader::LoadPysehdShader);
}

} // namespace python
} // namespace glove