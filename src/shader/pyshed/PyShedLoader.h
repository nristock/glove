#pragma once

#include <string>

#include <boost/python.hpp>

#include "core/GloveFwd.h"
#include <pitamem/MemoryProfile.h>

namespace glove {

class PyShedLoader {
Profilable();
public:
	PyShedLoader(GlovePythonEnginePointer pythonEngine);

    virtual ~PyShedLoader();

    ShaderProgramPointer LoadPysehdShader(std::string fileName);

private:
    boost::python::object CreatePyshedScope();

    GlovePythonEnginePointer pythonEngine;
};


} // namespace glove