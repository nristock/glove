#pragma once

#include <boost/python/dict.hpp>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

/** Class representing the python part of a plugin */
class PythonPlugin : public GloveObject {
Profilable()
public:
    PythonPlugin(std::string pluginPath, std::string pluginName);

    virtual ~PythonPlugin();

    /** Loads the plugin by calling its LoadPlugin method and creating the plugin scope */
    virtual void LoadPlugin();

    /** Unloads the plugin by calling its UnloadPlugin method */
    virtual void UnloadPlugin();

    /** Reloads the plugin by first calling UnloadPlugin, then reloading the python module and finally calling LoadPlugin again*/
    virtual void ReloadPlugin();

    /** Returns the plugin's name */
    virtual const std::string& GetPluginName() const {
        return pluginName;
    }

    /** Returns the plugin's scope */
    virtual const boost::python::dict& GetScope() const {
        return pluginScope;
    }

    /** Returns whether the plugin is currently loaded */
    virtual bool IsLoaded() const {
        return loaded;
    }

protected:
    /** Reference to the python engine initialized in constructor */
    GlovePythonEnginePtr pythonEngine;

    std::string pluginPath;
    std::string pluginName;
    boost::python::object pluginModule;
    boost::python::dict pluginScope;

    /** Initializes the plugin scope by appending the engine's root scope to the module's scope */
    virtual void InitPluginScope();

private:
    bool loaded;
};


} // namespace glove