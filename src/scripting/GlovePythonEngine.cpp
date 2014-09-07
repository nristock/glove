#include "GlovePythonEngine.h"

#include <locale>
#include <codecvt>
#include <stdio.h>

#include <boost/python.hpp>
#include <boost/filesystem.hpp>

#include "modules/glove/GloveModule.h"
#include "modules/pyshed/PyShedModule.h"

namespace bpy = boost::python;
namespace bfs = boost::filesystem;

namespace glove {

GlovePythonEngine::GlovePythonEngine() : GloveObject() {

}

GlovePythonEngine::~GlovePythonEngine() {

}

void GlovePythonEngine::Init(const std::wstring& executableBasePath) {
	basePath = executableBasePath;

	std::wstring  pythonHome(executableBasePath);
	pythonHome.append(L"/data/python;");
	pythonHome.append(executableBasePath);
	pythonHome.append(L"/data/game/modules");
	
	wchar_t* cstrPythonHome = reinterpret_cast<wchar_t*>(malloc(sizeof(wchar_t) * pythonHome.length()));
	wcscpy(cstrPythonHome, pythonHome.c_str());
	
	Py_SetPath(cstrPythonHome);
	OLOG(info, "Using Python in " << std::wstring(Py_GetPath()));
	
	PyImport_AppendInittab("glove", &python::CreateGloveModule);
	PyImport_AppendInittab("pysehd", &python::CreatePyshedModule);
	Py_Initialize();

	try {
		using namespace boost::python;
		LoadPyEnvironmentModule();

		/*{
			object main_module = import("__main__");


			//PyImport_AddModule("testmodule2");
			object test_module = import("testmodule.stuff");
			object ns = main_module.attr("__dict__");
			ns["k"] = test_module;
		}
		
		object main_module = import("__main__");
		object ns = main_module.attr("__dict__");*/
		dict ns = dict();
		exec("res=5", ns);
		object o2 = ns["res"];

		//ns["k"] = test_module;
		//object o2 = exec("k.test()", ns);
		//object str = str(o);
		std::string ot = extract<const char*>(str(o2));
		OLOG(info, ot);		
	}
	catch (boost::python::error_already_set const &) {
		HandleError();

	}

	OLOG(info, "Scripting engine initialized.");
}

void GlovePythonEngine::LoadPyEnvironmentModule() {
	bpy::object mainNS = GetMainNamespace();

	std::wstring gloveCorePythonEnvironmentDirBase = basePath;
	gloveCorePythonEnvironmentDirBase.append(L"/data/game/gcpyenv");

	bfs::path gloveCorePythonEnvDir(gloveCorePythonEnvironmentDirBase);
	for (bfs::directory_entry t : bfs::directory_iterator(gloveCorePythonEnvDir)) {
		if (bfs::is_regular_file(t)) {
			OLOG(info, "Loading python environment file: " << t.path().filename().string());

			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
			std::string s = converter.to_bytes(t.path().wstring());
			
			bpy::exec_file(s.c_str(), mainNS);
		}
	}

	OLOG(info, "PyEnv files loaded");
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

bpy::object GlovePythonEngine::GetMainModule() {
	return bpy::import("__main__");
}

bpy::object GlovePythonEngine::GetMainNamespace() {
	return GetMainModule().attr("__dict__");
}

} //namespace glove
