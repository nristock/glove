#ifndef SCRIPTING_MODULES_PYSHED_PYSHEDMODULE_H_
#define SCRIPTING_MODULES_PYSHED_PYSHEDMODULE_H_

#include <boost/python.hpp>

namespace glove {
namespace python {
PyObject* CreatePyshedModule();
} // namespace python
} // namespace glove

#endif