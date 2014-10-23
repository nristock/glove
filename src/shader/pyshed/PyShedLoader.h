#pragma once

#include <string>

#include <boost/python.hpp>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

class PyShedLoader : public GloveObject {
Profilable()
public:
    PyShedLoader(GlovePythonEnginePointer pythonEngine);

    virtual ~PyShedLoader();

    ShaderProgramPointer LoadPysehdShader(std::string fileName);

private:
    boost::python::object CreatePyshedScope();

    GlovePythonEnginePointer pythonEngine;
};


} // namespace glove