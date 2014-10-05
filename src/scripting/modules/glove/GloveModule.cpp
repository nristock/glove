// GENERATED CODE - DO NOT MODIFY
#include "GloveModule.h"

#include "PyCamera.h"
#include "PyCoreComponents.h"
#include "PyGameObject.h"
#include "PyGloveCore.h"
#include "PyGloveObject.h"
#include "PyScenegraph.h"
#include "PyGlovePythonEngine.h"
#include "PyGloveRenderer.h"
#include "PyGpuBufferManager.h"
#include "PyPyShedLoader.h"
#include "PyGPUBuffer.h"
#include "PyGameComponent.h"

namespace glove {
namespace python {
BOOST_PYTHON_MODULE(GloveModule) {
	ExportGloveObject();
	ExportCoreComponents();
	ExportGameObject();
	ExportCamera();
	ExportGlovePythonEngine();
	ExportGloveRenderer();
	ExportGPUBuffer();
	ExportGpuBufferManager();
	ExportPyShedLoader();
	ExportGloveCore();
	ExportScenegraph();
	ExportGameComponent();
}

PyObject* CreateGloveModule() {
	return PyInit_GloveModule();
}
} // namespace python
} // namespace glove

