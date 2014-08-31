#include "GloveModule.h"

#include "PyGloveCore.h"
#include "PyGloveObject.h"

namespace glove {
namespace python {
BOOST_PYTHON_MODULE(GloveModule) {
	ExportGloveCore();
	ExportGloveObject();
}

PyObject* CreateGloveModule() {
	return PyInit_GloveModule();
}
} // namespace python
} // namespace glove

