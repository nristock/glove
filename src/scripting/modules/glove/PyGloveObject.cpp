#include "PyGloveObject.h"

#include <boost/python.hpp>

#include "core/GloveObject.h"

namespace glove {
namespace python {

void ExportGloveObject() {
	boost::python::class_<glove::GloveObject>("GloveObject");
}

} // namespace python
} // namespace glove