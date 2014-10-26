#include "PyGloveRenderer.h"

#include <boost/python.hpp>

#include "rendering/opengl/GLRenderer.h"

namespace glove {
namespace python {

void ExportGloveRenderer() {
	boost::python::class_<glove::GLRenderer, std::shared_ptr<GLRenderer>>("GLRenderer", boost::python::no_init);
}

} // namespace python
} // namespace glove