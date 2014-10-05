#ifndef CORE_GLOVEPLUGIN_H_
#define CORE_GLOVEPLUGIN_H_

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

/** This class represents a glove engine plugin */
class GlovePlugin : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GlovePlugin")
public:
	/** Creates and "discovers" (imports) the plugin */
	GlovePlugin(std::string name);
	virtual ~GlovePlugin();

	/** Loads the plugin */
	virtual void LoadPlugin();
	/** Reloads the plugin */
	virtual void ReloadPlugin();
	/** Unloads the plugin */
	virtual void UnloadPlugin();

	/** Returns a shared pointer to the corresponding python plugin */
	virtual PythonPluginPtr GetPythonPlugin() const { return pythonPlugin; }

protected:
	/** The plugin's name */
	std::string name;
	/** The plugin's base directory */
	std::string pluginBasePath;
	/** The plugin's scripts directory */
	std::string scriptsPath;
	
	PythonPluginPtr pythonPlugin;
};


} // namespace glove

#endif