#include "PythonPlugin.h"

#include <boost/python.hpp>
#include <boost/format.hpp>

#include "core/GloveCore.h"
#include "core/GloveException.h"
#include "scripting/GlovePythonEngine.h"

namespace bpy = boost::python;

namespace glove {

PythonPlugin::PythonPlugin(std::string pluginPath, std::string pluginName)
        : GloveObject(), pluginPath(pluginPath), pluginName(pluginName), loaded(false), EnableProfilable() {
    pythonEngine = gloveCore->GetPythonEngine();

    // Import the plugin module
    pluginModule = bpy::import(pluginName.c_str());

    InitPluginScope();
}

PythonPlugin::~PythonPlugin() {

}

void PythonPlugin::InitPluginScope() {
    // Get the module's scope and append a copy of the root namespace
    pluginScope = bpy::extract<bpy::dict>(pluginModule.attr("__dict__"));
    pluginScope["__name__"] = bpy::str(pluginName);
    pluginScope["__moduledir__"] = bpy::str(pluginPath);
    pluginScope.update(pythonEngine->GetRootNamespace().copy());
}

void PythonPlugin::LoadPlugin() {
    if (IsLoaded()) {
        OLOG(warning, (boost::format("Loading active plugin %1%") % pluginName).str());
    }

    OLOG(info, "Loading python plugin: " << pluginName);

    try {
        if (pluginScope.contains("LoadPlugin")) {
            pluginScope["LoadPlugin"]();
        }

        loaded = true;
    }
    catch (const boost::python::error_already_set&) {
        pythonEngine->HandleError();
    }
}

void PythonPlugin::UnloadPlugin() {
    if (!IsLoaded()) {
        OLOG(error, (boost::format("Unloading inactive plugin %1%") % pluginName).str());
        return;
    }

    OLOG(info, "Unloading python plugin: " << pluginName);

    try {
        loaded = false;

        if (pluginScope.contains("UnloadPlugin")) {
            pluginScope["UnloadPlugin"]();
        }
    }
    catch (const boost::python::error_already_set&) {
        pythonEngine->HandleError();
    }
}

void PythonPlugin::ReloadPlugin() {
    UnloadPlugin();

    PyObject* newModule = PyImport_ReloadModule(pluginModule.ptr());
    if (newModule == NULL) {
        pythonEngine->HandleError();

        throw GLOVE_EXCEPTION((boost::format("Failed to reload plugin %1%") % pluginName).str());
    }

    bpy::handle<> moduleHandle(newModule);
    pluginModule = bpy::object(moduleHandle);

    InitPluginScope();
    LoadPlugin();
}

} // namespace glove