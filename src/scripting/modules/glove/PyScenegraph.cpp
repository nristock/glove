#include "PyScenegraph.h"

#include <boost/python.hpp>
#include <scripting/PythonObjectFactory.h>

#include "graph/Scenegraph.h"

namespace glove {
namespace python {

void ExportScenegraph() {
    boost::python::class_<glove::Scenegraph, std::shared_ptr<Scenegraph>>("Scenegraph")
            .def("CreateGameObject", &Scenegraph::CreateSimpleGameObject)
            .def("CreateCamera", &Scenegraph::CreateCamera)
            .def("SetActiveCamera", &Scenegraph::SetActiveCamera);
}

} // namespace python
} // namespace glove