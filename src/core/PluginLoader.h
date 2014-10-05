#ifndef CORE_PLUGINLOADER_H_
#define CORE_PLUGINLOADER_H_

#include <map>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

class PluginLoader : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("PluginLoader")
public:
	/** Name <-> Plugin map type */
	typedef std::map<std::string, GlovePluginPtr> PluginMap;

	PluginLoader();
	virtual ~PluginLoader();

	/** Discovers all plugins in /data/game/plugins/ */
	virtual void DiscoverPlugins();
	/** Loads all discovered plugins */
	virtual void LoadPlugins();
	/** Unloads all discovered and loaded plugins */
	virtual void UnloadPlugins();
	
	/** 
	 * Discoveres a single plugin by name 
	 * When a plugin is discovered it will be imported as a python plugin and it will be added to the list of discovered plugins.
	 */
	virtual GlovePluginPtr DiscoverPlugin(std::string name);
	/** Unloads a single plugin by name */
	virtual void UnloadPlugin(std::string name);
	/** Reloads a single plugin by name */
	virtual void ReloadPlugin(std::string name);

private:
	/** The map of discovered plugins */
	PluginMap pluginMap;

	/** Base plugin search path; usually /data/game/plugins/ */
	std::string pluginBasePath;
};


} // namespace glove

#endif