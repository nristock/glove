#include "PyScenegraph.h"

#include <boost/python.hpp>

#include "graph/Scenegraph.h"

namespace glove {
namespace python {

void ExportScenegraph() {
	boost::python::class_<glove::Scenegraph, boost::python::bases<GloveObject>, std::shared_ptr<Scenegraph>>("Scenegraph")
		.def("CreateGameObject", &Scenegraph::CreateGameObject)
		.def("CreateCamera", &Scenegraph::CreateCamera)
		.def("SetActiveCamera", &Scenegraph::SetActiveCamera);
}

} // namespace python
} // namespace glove