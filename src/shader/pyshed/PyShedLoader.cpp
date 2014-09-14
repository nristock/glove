#include "PyShedLoader.h"

#include "scripting/GlovePythonEngine.h"
#include "shader/ShaderProgram.h"

#include "utils/FileUtils.h"

namespace bpy = boost::python;

namespace glove {
	
PyShedLoader::PyShedLoader(GlovePythonEnginePointer pythonEngine) {
	this->pythonEngine = pythonEngine;
}

PyShedLoader::~PyShedLoader() {
	
}

ShaderProgramPointer PyShedLoader::LoadPysehdShader(std::string fileName) {
	bpy::object scope = CreatePyshedScope();

	try {
		bpy::exec_file(fileName.c_str(), scope);
		return bpy::extract<ShaderProgramPointer>(scope["shader"]);
	}
	catch (boost::python::error_already_set const &) {
		pythonEngine->HandleError();
	}
}

bpy::object PyShedLoader::CreatePyshedScope() {
	try {
		bpy::dict scope(pythonEngine->GetMainNamespace());
		bpy::exec("from pyshed import *", scope);
		bpy::exec("shader = ShaderProgram(2)", scope);

		return scope;
	}
	catch (boost::python::error_already_set const &) {
		pythonEngine->HandleError();
	}	

	return bpy::object();
}

} // namespace glove