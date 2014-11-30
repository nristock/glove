#pragma once

#include "core/GloveFwd.h"

#include <pitamem/MemoryProfile.h>

namespace glove {

/** This class represents a glove engine plugin */
class GlovePlugin {
    Profilable();

  public:
    /** Creates and "discovers" (imports) the plugin */
    GlovePlugin(const GlovePythonEnginePtr& pythonEngine, std::string name);

    virtual ~GlovePlugin();

    /** Loads the plugin */
    virtual void LoadPlugin();

    /** Reloads the plugin */
    virtual void ReloadPlugin();

    /** Unloads the plugin */
    virtual void UnloadPlugin();

    virtual bool IsLoaded() const;

    /** Returns a shared pointer to the corresponding python plugin */
    virtual PythonPluginPtr GetPythonPlugin() const { return pythonPlugin; }

  protected:
    GlovePythonEnginePtr pythonEngine;

    /** The plugin's name */
    std::string name;
    /** The plugin's base directory */
    std::string pluginBasePath;
    /** The plugin's scripts directory */
    std::string scriptsPath;

    /** Reference to the corresponding python plugin */
    PythonPluginPtr pythonPlugin;
};

} // namespace glove