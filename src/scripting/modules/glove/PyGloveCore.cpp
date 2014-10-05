#include "PyGloveCore.h"

#include <boost/python.hpp>

namespace glove {
namespace python {

void ExportGloveCore() {
	boost::python::class_<glove::GloveCore, boost::python::bases<GloveObject>, std::shared_ptr<GloveCore>>("GloveCore")
		.def("GetScenegraph", &GloveCore::GetScenegraph)
		.def("GetPythonEngine", &GloveCore::GetPythonEngine)
		.def("GetPyshedLoader", &GloveCore::GetPyshedLoader)
		.def("GetRenderer", &GloveCore::GetRenderer)
		.def("GetGpuBufferManager", &GloveCore::GetGpuBufferManager)
		.def("MakeDataPath", &GloveCore::MakeDataPath)
		.add_property("exitRequested", &GloveCore::IsExitRequested, &GloveCore::SetExitRequested);
}

} // namespace python
} // namespace glove