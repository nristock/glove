#include "PyShaderProgram.h"

#include <boost/python.hpp>
#include <scripting/PythonObjectFactory.h>

#include "shader/ShaderProgram.h"

namespace glove {
namespace python {

void ExportShader() {
	boost::python::class_<glove::ShaderProgram, std::shared_ptr<ShaderProgram>>("ShaderProgram", boost::python::init<int>())
		.def("MapVertexAttribute", &ShaderProgram::MapVertexAttribute)
		.def("MapMaterialAttribute", &ShaderProgram::MapMaterialAttribute)
		.def("LoadShader", &ShaderProgram::LoadShader)
		.def("LoadVertexShader", &ShaderProgram::LoadVertexShader)
		.def("LoadFragmentShader", &ShaderProgram::LoadFragmentShader)
		.def("CreateProgram", &ShaderProgram::CreateProgram);
}

} // namespace python
} // namespace glove