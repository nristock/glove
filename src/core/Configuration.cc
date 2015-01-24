#include "Configuration.h"
#include "GloveException.h"

#include <fstream>

#include <boost/format.hpp>
#include <vendor/json/json.h>

namespace glove {

void Configuration::LoadFromFile(const std::string& filePath) {
    std::ifstream configFile(filePath);

    Json::Value rootJsonNode;
    Json::Reader jsonReader;

    bool parsedSuccessfully = jsonReader.parse(configFile, rootJsonNode, false);
    if (!parsedSuccessfully)
        throw GLOVE_EXCEPTION(
            (boost::format("Failed to parse JSON istream:\n%1%") % jsonReader.getFormattedErrorMessages()).str());

    rendering.window.height = rootJsonNode["rendering"]["window"]["height"].asInt();
    rendering.window.width = rootJsonNode["rendering"]["window"]["width"].asInt();

    rendering.opengl.versionMajor = rootJsonNode["rendering"]["opengl"]["major"].asInt();
    rendering.opengl.versionMinor = rootJsonNode["rendering"]["opengl"]["minor"].asInt();

    for (auto& subsys : rootJsonNode["engine"]["subsystems"]["init"]) {
        engine.subsystemInitList.push_back(subsys.asString());
    }

    engine.loadNativeExtensions = rootJsonNode["engine"]["load-natex"].asBool();
}

void Configuration::SaveToFile(const std::string& path) {
    Json::Value rootNode = Json::objectValue;

    /////////////////////////////////////////////////////////////////////////////
    Json::Value renderingNode = Json::objectValue;

    Json::Value windowNode = Json::objectValue;
    windowNode["height"] = rendering.window.height;
    windowNode["width"] = rendering.window.width;
    renderingNode["window"] = windowNode;

    Json::Value openglNode = Json::objectValue;
    openglNode["major"] = rendering.opengl.versionMajor;
    openglNode["minor"] = rendering.opengl.versionMinor;
    renderingNode["opengl"] = openglNode;

    rootNode["rendering"] = renderingNode;

    /////////////////////////////////////////////////////////////////////////////
    Json::Value engineNode = Json::objectValue;

    Json::Value subsystemsNode = Json::objectValue;
    Json::Value initList = Json::arrayValue;
    for (auto& subsys : engine.subsystemInitList) {
        initList.append(subsys);
    }
    engineNode["subsystems"] = subsystemsNode;
    engineNode["load-natex"] = engine.loadNativeExtensions;

    rootNode["engine"] = engineNode;

    std::ofstream configFile(path);
    Json::StyledStreamWriter writer;
    writer.write(configFile, rootNode);
}

void Configuration::LoadDefaults() {
    rendering.window.height = 600;
    rendering.window.width = 800;

    rendering.opengl.versionMinor = 3;
    rendering.opengl.versionMajor = 3;

    engine.subsystemInitList.push_back("rendering");
    engine.subsystemInitList.push_back("scripting");
    engine.loadNativeExtensions = true;
}
}