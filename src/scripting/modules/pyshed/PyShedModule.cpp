#include "PyShedModule.h"

#include "shader/MappedVertexAttribute.h"
#include "PyShaderProgram.h"

#include "scripting/modules/glove/PyGloveObject.h"

namespace bpy = boost::python;

namespace glove {
namespace python {
BOOST_PYTHON_MODULE(PyshedModule) {
	ExportGloveObject();

	bpy::enum_<MappedVertexAttribute>("MVA")
		.value("COLORS", MVA_COLORS)
		.value("POSITIONS", MVA_POSITIONS);

	ExportShader();
}

PyObject* CreatePyshedModule() {
	return PyInit_PyshedModule();
}

} // namespace python
} // namespace glove