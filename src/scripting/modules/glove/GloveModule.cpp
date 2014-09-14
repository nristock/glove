// GENERATED CODE - DO NOT MODIFY
#include "GloveModule.h"

#include "PyCamera.h"
#include "PyCoreComponents.h"
#include "PyGameObject.h"
#include "PyGloveCore.h"
#include "PyGloveObject.h"
#include "PyScenegraph.h"

namespace glove {
namespace python {
BOOST_PYTHON_MODULE(GloveModule) {
	ExportGloveObject();
	ExportCoreComponents();
	ExportGameObject();
	ExportCamera();
	ExportGloveCore();
	ExportScenegraph();
}

PyObject* CreateGloveModule() {
	return PyInit_GloveModule();
}
} // namespace python
} // namespace glove

