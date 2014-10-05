#include "PluginLoader.h"

#include <boost/filesystem.hpp>
#include <boost/format.hpp>

#include "core/GloveCore.h"
#include "core/GlovePlugin.h"

#include "scripting/GlovePythonEngine.h"

namespace bfs = boost::filesystem;

namespace glove {

PluginLoader::PluginLoader() {
	pluginBasePath = gloveCore->MakeDataPath("data/game/plugins");
}

PluginLoader::~PluginLoader() {
	UnloadPlugins();
}

void PluginLoader::DiscoverPlugins() {
	// Discover plugins and import the corresponding python modules
	bfs::path gloveCorePythonEnvDir(pluginBasePath);
	for (bfs::directory_entry dir : bfs::directory_iterator(gloveCorePythonEnvDir)) {
		if (bfs::is_directory(dir)) {
			std::string pluginName = dir.path().filename().string();
			try {
				DiscoverPlugin(pluginName);
			}
			catch (const GloveException& ex) {
				OLOG(error, ((boost::format("Failed to load plugin %1%: %2%") % pluginName % ex.what()).str()))
			}
		}
	}
}

void PluginLoader::LoadPlugins() {
	for (auto plugin : pluginMap) {
		plugin.second->LoadPlugin();
	}
}

void PluginLoader::UnloadPlugins() {
	for (auto plugin : pluginMap) {
		plugin.second->UnloadPlugin();
	}
}

GlovePluginPtr PluginLoader::DiscoverPlugin(std::string name) {
	// Create and import the plugin
	GlovePluginPtr plugin = std::make_shared<GlovePlugin>(name);
	pluginMap[name] = plugin;
	gloveCore->GetPythonEngineRef()->AnnouncePlugin(plugin->GetPythonPlugin());

	OLOG(info, (boost::format("Discovered plugin %1%") % name).str());
	return plugin;
}

void PluginLoader::UnloadPlugin(std::string name) {
	auto plugin = pluginMap.find(name);
	if (plugin != pluginMap.end()) {
		plugin->second->UnloadPlugin();
	}
}

void PluginLoader::ReloadPlugin(std::string name) {
	auto plugin = pluginMap.find(name);
	if (plugin != pluginMap.end()) {
		plugin->second->ReloadPlugin();
	}
}

} // namespace glove