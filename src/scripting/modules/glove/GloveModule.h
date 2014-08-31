#ifndef SCRIPTING_MODULES_GLOVE_GLOVEMODULE_H_
#define SCRIPTING_MODULES_GLOVE_GLOVEMODULE_H_

#include <boost/python.hpp>

namespace glove {
namespace python {
PyObject* CreateGloveModule();
} // namespace python
} // namespace glove

#endif