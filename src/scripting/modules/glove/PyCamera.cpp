#include "PyCamera.h"

#include <boost/python.hpp>

#include "rendering/Camera.h"

namespace glove {
namespace python {

void ExportCamera() {
	boost::python::class_<glove::Camera, boost::python::bases<GameObject, GloveObject>, std::shared_ptr<Camera>>("Camera");
}

} // namespace python
} // namespace glove