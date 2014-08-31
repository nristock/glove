#include "GlovePythonEngine.h"

#include <boost/python.hpp>

#include "modules/glove/GloveModule.h"

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
	
	Py_SetPath(cstrPythonHome);
	OLOG(info, "Using Python in " << std::wstring(Py_GetPath()));
	
	PyImport_AppendInittab("glove", &python::CreateGloveModule);
	Py_Initialize();

	try {
		using namespace boost::python;
		object main_module = import("__main__");
		object ns = main_module.attr("__dict__");
		object o = exec("5**5", ns);
		std::string ot = extract<std::string>(str(o));
		OLOG(info, ot);
	}
	catch (boost::python::error_already_set const &) {
		HandleError();

	}

	OLOG(info, "Scripting engine initialized.");
}

void GlovePythonEngine::HandleError() {
	PyObject* pyType;
	PyObject* pyValue;
	PyObject* pyTraceback;

	PyErr_Fetch(&pyType, &pyValue, &pyTraceback);
	PyErr_NormalizeException(&pyType, &pyValue, &pyTraceback);
	if (pyType == NULL && pyValue == NULL && pyTraceback == NULL) {
		OLOG(warning, "GPythonEngine::HandleError() called but no error was set.");
	}

	bool hasTraceback = pyTraceback != NULL;

	using namespace boost::python;
	handle<> hType(pyType);
	object exType(hType);

	handle<> hValue(pyValue);
	object exValue(hValue);

	std::wstring errorType = extract <std::wstring>(exType.attr("__name__"));
	std::wstring errorMessage = extract<std::wstring>(str(exValue));	

	std::wstringstream tracebackString;

	if (hasTraceback) {
		handle<> hTraceback(pyTraceback);
		object exTraceback(hTraceback);
		object currentTraceback = exTraceback;
		while (!currentTraceback.is_none())
		{
			int line = extract<long>(currentTraceback.attr("tb_lineno"));
			std::wstring file = extract<std::wstring>(currentTraceback.attr("tb_frame").attr("f_code").attr("co_filename"));
			std::wstring function = extract<std::wstring>(currentTraceback.attr("tb_frame").attr("f_code").attr("co_name"));

			tracebackString << "in " << function << " (" << file << ":" << line << ")" << std::endl;

			currentTraceback = currentTraceback.attr("tb_next");
		}
	}
	else if (PyErr_GivenExceptionMatches(pyType, PyExc_SyntaxError)) {
		std::wstring text = extract<std::wstring>(exValue.attr("text"));
		int offset = extract<int>(exValue.attr("offset"));
		tracebackString << text << std::wstring(offset - 2, ' ') << "^";
	}

	OLOG(info, "Python Error" << std::endl << errorType << ": " << errorMessage << std::endl << tracebackString.str());
}

void GlovePythonEngine::Exit() {
	Py_Finalize();
}

} //namespace glove
