#include "PyGloveRenderer.h"

#include <boost/python.hpp>

#include "rendering/opengl/GLRenderer.h"

namespace glove {
namespace python {

void ExportGloveRenderer() {
	boost::python::class_<glove::GLRenderer, boost::python::bases<GloveObject>, std::shared_ptr<GLRenderer>>("GLRenderer");
}

} // namespace python
} // namespace glove