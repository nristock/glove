#include "PyGameObject.h"

#include <boost/python.hpp>

#include "graph/GameObject.h"

namespace glove {
namespace python {

void ExportGameObject() {
	boost::python::class_<glove::GameObject, boost::python::bases<GloveObject>, std::shared_ptr<GameObject>>("GameObject")
		.def("AddComponent", &GameObject::AddUniqueComponent);
}

} // namespace python
} // namespace glove