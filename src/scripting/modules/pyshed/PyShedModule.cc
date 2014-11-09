#include "PyShedModule.h"

#include "rendering/vertex/VertexAttributeSemantic.h"
#include "PyShaderProgram.h"

#include "shader/MappedMaterialAttribute.h"
#include "PyMaterial.h"

namespace bpy = boost::python;

namespace glove {
namespace python {
BOOST_PYTHON_MODULE(PyshedModule) {
	bpy::enum_<VertexAttributeSemantic>("VAS")
		.value("COLOR", VAS_COLOR)
		.value("NORMAL", VAS_NORMAL)
		.value("POSITION", VAS_POSITION);

	bpy::enum_<MappedMaterialAttribute>("MMA")
		.value("MAT_MVP", MMA_MAT_MVP);

	ExportShader();
	ExportMaterial();
}

PyObject* CreatePyshedModule() {
	return PyInit_PyshedModule();
}

} // namespace python
} // namespace glove