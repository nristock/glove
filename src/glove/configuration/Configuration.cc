#include <fstream>

#include <boost/format.hpp>

#include "glove/DwarfException.hpp"
#include "glove/configuration/Configuration.hpp"
#include "glove/configuration/ConfigurationConverters.hpp"

namespace BlueDwarf {

Configuration Configuration::LoadFromFile(const std::string& filePath) {
    try {
        YAML::Node config = YAML::LoadFile(filePath);
        Configuration deserializedConfig = config.as<Configuration>();
        deserializedConfig.configurationRoot = config;

        return deserializedConfig;
    } catch (YAML::Exception& ex) {
        DWARF_THROW(DwarfException, ex.what());
    } catch (std::runtime_error& ex) {
        DWARF_THROW(DwarfException, ex.what());
    } catch (DwarfException& ex) {
        throw;
    }
}

void Configuration::SaveToFile(const std::string& path) {
    YAML::Node config(*this);

    std::ofstream configFile(path);
    configFile << config;
}

void Configuration::LoadDefaults() {
    rendering.window.height = 600;
    rendering.window.width = 800;

    rendering.opengl.version.minor = 3;
    rendering.opengl.version.major = 3;

    engine.loadNativeExtensions = true;
}
}
