#include "Configuration.hpp"

#include <fstream>

#include <boost/format.hpp>

#include "GloveException.h"
#include "core/configuration/ConfigurationConverters.hpp"

namespace glove {

Configuration Configuration::LoadFromFile(const std::string& filePath) {
    try {
        YAML::Node config = YAML::LoadFile(filePath);
        Configuration deserializedConfig = config.as<Configuration>();
        deserializedConfig.configurationRoot = config;

        return deserializedConfig;
    } catch (YAML::Exception& ex) {
        GLOVE_THROW(GloveException, ex.what());
    } catch (std::runtime_error& ex) {
        GLOVE_THROW(GloveException, ex.what());
    } catch (GloveException& ex) {
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
