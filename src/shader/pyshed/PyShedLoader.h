#ifndef SHADER_PYSHED_PYSHEDLOADER_H_
#define SHADER_PYSHED_PYSHEDLOADER_H_

#include <string>

#include <boost/python.hpp>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

class PyShedLoader : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("PyShedLoader")
public:
	PyShedLoader(GlovePythonEnginePointer pythonEngine);
	virtual ~PyShedLoader();

	ShaderPointer LoadPysehdShader(std::string fileName);

private:
	boost::python::object CreatePyshedScope();

	GlovePythonEnginePointer pythonEngine;
};


} // namespace glove

#endif