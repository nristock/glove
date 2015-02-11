#include <boost/format.hpp>

#include "glove/GlovePlugin.hpp"
#include "glove/GloveException.hpp"
#include "glove/GloveCore.hpp"
#include "scripting/GlovePythonEngine.h"
#include "scripting/PythonPlugin.h"
#include "GloveEnvironment.h"

namespace glove {

GlovePlugin::GlovePlugin(const GlovePythonEnginePtr& pythonEngine, std::string name)
    : pythonEngine(pythonEngine), name(name), EnableProfilable() {
    pluginBasePath = gEnv->MakeDataPath((boost::format("data/game/plugins/%1%") % name).str());
    scriptsPath = (boost::format("%1%/scripts") % pluginBasePath).str();

    try {
        pythonPlugin = std::make_shared<PythonPlugin>(pythonEngine, pluginBasePath, name);
    } catch (const boost::python::error_already_set&) {
        pythonEngine->HandleError();

        throw GLOVE_EXCEPTION(
            (boost::format("Failed to create initialize plugin %1% because the python plugin couldn't be imported.") %
             name).str());
    }
}

GlovePlugin::~GlovePlugin() {
}

void GlovePlugin::LoadPlugin() {
    pythonPlugin->LoadPlugin();
}

void GlovePlugin::ReloadPlugin() {
    pythonPlugin->ReloadPlugin();
}

void GlovePlugin::UnloadPlugin() {
    pythonPlugin->UnloadPlugin();
}

bool GlovePlugin::IsLoaded() const {
    return pythonPlugin->IsLoaded();
}
} // namespace glove