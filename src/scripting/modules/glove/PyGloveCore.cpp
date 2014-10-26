#include "PyGloveCore.h"

#include <boost/python.hpp>

namespace glove {
namespace python {

void ExportGloveCore() {
	boost::python::class_<glove::GloveCore, std::shared_ptr<GloveCore>, boost::noncopyable>("GloveCore", boost::python::no_init)
		.def("GetScenegraph", &GloveCore::GetScenegraph, boost::python::return_value_policy<boost::python::copy_const_reference>())
		.def("GetPythonEngine", &GloveCore::GetPythonEngine, boost::python::return_value_policy<boost::python::copy_const_reference>())
		.def("GetPyshedLoader", &GloveCore::GetPyshedLoader, boost::python::return_value_policy<boost::python::copy_const_reference>())
		.def("GetRenderer", &GloveCore::GetRenderer, boost::python::return_value_policy<boost::python::copy_const_reference>())
		.def("GetGpuBufferManager", &GloveCore::GetGpuBufferManager, boost::python::return_value_policy<boost::python::copy_const_reference>())
		.add_property("exitRequested", &GloveCore::IsExitRequested, &GloveCore::SetExitRequested);
}

} // namespace python
} // namespace glove