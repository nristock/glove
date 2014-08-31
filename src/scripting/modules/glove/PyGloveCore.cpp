#include "PyGloveCore.h"

#include <boost/python.hpp>

namespace glove {
namespace python {

void ExportGloveCore() {
	boost::python::class_<glove::GloveCore, boost::python::bases<GloveObject>>("GloveCore");
}

} // namespace python
} // namespace glove