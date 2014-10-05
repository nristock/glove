#include "PyGloveRenderer.h"

#include <boost/python.hpp>

#include "rendering/GloveRenderer.h"

namespace glove {
namespace python {

void ExportGloveRenderer() {
	boost::python::class_<glove::GloveRenderer, boost::python::bases<GloveObject>, std::shared_ptr<GloveRenderer>>("GloveRenderer");
}

} // namespace python
} // namespace glove