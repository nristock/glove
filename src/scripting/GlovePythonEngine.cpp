#include "GlovePythonEngine.h"

#include <stdio.h>

#include <boost/format.hpp>
#include <boost/python.hpp>
#include <boost/filesystem.hpp>

#include "core/GloveException.h"
#include "scripting/PythonPlugin.h"
#include "modules/glove/GloveModule.h"
#include "modules/pyshed/PyShedModule.h"

namespace bpy = boost::python;
namespace bfs = boost::filesystem;

namespace glove {

GlovePythonEngine::GlovePythonEngine(const std::string& executableBasePath) : GloveObject(), basePath(executableBasePath) {
	std::wstringstream wstringConverter = std::wstringstream();
	wstringConverter << executableBasePath.c_str();
	std::wstring wideBasePath = wstringConverter.str();

	std::wstring pythonHome = (boost::wformat(L"%1%/data/python;%1%/data/game/modules;%1%/data/game/plugins") % wideBasePath).str();
	wchar_t* cstrPythonHome = GLOVE_NEW_ARRAY("GlovePythonEngine/cstrPythonHome", wchar_t, pythonHome.length());
	wcscpy(cstrPythonHome, pythonHome.c_str());

	try {
		Py_SetPath(cstrPythonHome);
		OLOG(info, "Using Python in " << std::wstring(Py_GetPath()));

		PyImport_AppendInittab("glove", &python::CreateGloveModule);
		PyImport_AppendInittab("pyshed", &python::CreatePyshedModule);
		Py_Initialize();

		using namespace boost::python;

		// Init root namespace
		dict builtinDict = GetBuiltins();
		rootNamespace["__builtins__"] = builtinDict;
		rootNamespace["__plugins__"] = pluginScopes;
		rootNamespace["sys"] = import("sys");

		// Add glove module types to builtins
		dict gloveModuleDict = extract<dict>(import("glove").attr("__dict__"));
		builtinDict.update(gloveModuleDict);

		LoadPyEnvironmentModule();
	}
	catch (const boost::python::error_already_set&) {
		HandleError();

		throw GLOVE_EXCEPTION("Failed to create scripting engine.");
	}

	OLOG(info, "Scripting engine initialized.");
}

GlovePythonEngine::~GlovePythonEngine() {
	// Unload all plugins
	for (PythonPluginPtr plugin : plugins) {
		if (plugin->IsLoaded()) {
			plugin->UnloadPlugin();
		}
	}

	Py_Finalize();
}

void GlovePythonEngine::LoadPyEnvironmentModule() {
	std::string gloveCorePythonEnvironmentDirBase = basePath;
	gloveCorePythonEnvironmentDirBase.append("/data/game/gcpyenv");

	bfs::path gloveCorePythonEnvDir(gloveCorePythonEnvironmentDirBase);
	for (bfs::directory_entry dir : bfs::directory_iterator(gloveCorePythonEnvDir)) {
		if (bfs::is_regular_file(dir)) {
			OLOG(info, "Loading python environment file: " << dir.path().filename().string());

			std::string path = dir.path().string();
			bpy::exec_file(path.c_str(), rootNamespace);
		}
	}

	OLOG(info, "PyEnv files loaded");
}

void GlovePythonEngine::AnnouncePlugin(const PythonPluginPtr& pythonPlugin) {
	if (pluginScopes.contains(pythonPlugin->GetPluginName().c_str())) {
		OLOG(warning, (boost::format("Plugin %1% has already been announced. Overwriting previous dict") % pythonPlugin->GetPluginName()).str());
	}

	pluginScopes[pythonPlugin->GetPluginName().c_str()] = pythonPlugin->GetScope();
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
	
	using namespace boost::python;
	handle<> hType(pyType);
	handle<> hValue(allow_null(pyValue));
	handle<> hTraceback(allow_null(pyTraceback));
	
	std::string error;
	if (hValue) {
		object traceback(import("traceback"));
		object formatException(traceback.attr("format_exception"));
		object formattedList(formatException(hType, hValue, hTraceback));
		object formatted(str("").join(formattedList));

		error = extract<std::string>(formatted);
	}
	else {
		error = extract<std::string>(str(hType));
	}

	OLOG(info, "Python Error" << std::endl << error);
}

bpy::object GlovePythonEngine::GetMainModule() {
	return bpy::import("__main__");
}

bpy::dict GlovePythonEngine::GetRootNamespace() {
	return rootNamespace;
}

bpy::dict GlovePythonEngine::GetBuiltins() {
	return bpy::extract<bpy::dict>(GetMainModule().attr("__dict__")["__builtins__"].attr("__dict__"));
}

} //namespace glove
