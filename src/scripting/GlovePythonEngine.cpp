#include "GlovePythonEngine.h"

#include <Python.h>

namespace glove {

GlovePythonEngine::GlovePythonEngine() : GloveObject() {

}

GlovePythonEngine::~GlovePythonEngine() {

}

void GlovePythonEngine::Init(const std::wstring& executableBasePath) {
	std::wstring  pythonHome(executableBasePath);
	pythonHome.append(L"/data/python");

	wchar_t* cstrPythonHome = reinterpret_cast<wchar_t*>(malloc(sizeof(wchar_t) * pythonHome.length()));
	wcscpy(cstrPythonHome, pythonHome.c_str());
	
	Py_SetPythonHome(cstrPythonHome);

	OLOG(info, "Using Python in " << std::wstring(Py_GetPythonHome()));
	Py_Initialize();

	OLOG(info, "Scripting engine initialized.");
}

void GlovePythonEngine::Exit() {
	Py_Finalize();
}

} //namespace glove