#pragma once

#include <yaml-cpp/yaml.h>

#include "glove/DwarfException.hpp"
#include "glove/configuration/Configuration.hpp"

namespace YAML {
template<> struct BD_API_EXPORT convert<BlueDwarf::configuration::WindowConfig> {
    static Node encode(const BlueDwarf::configuration::WindowConfig& config) {
        Node node;
        node["width"] = config.width;
        node["height"] = config.height;

        return node;
    }

    static bool decode(const Node& node, BlueDwarf::configuration::WindowConfig& config) {
        if(!node.IsMap()) {
            throw DWARF_EXCEPTION("rendering.window has to be a map");
        }

        if(!node["width"].IsScalar()) {
            throw DWARF_EXCEPTION("rendering.window.width has to be an integer");
        }

        if(!node["height"].IsScalar()) {
            throw DWARF_EXCEPTION("rendering.window.height has to be an integer");
        }

        config.width = node["width"].as<int>();
        config.height = node["height"].as<int>();

        return true;
    }
};

template<> struct BD_API_EXPORT convert<BlueDwarf::configuration::OpenGLVersion> {
    static Node encode(const BlueDwarf::configuration::OpenGLVersion& config) {
        Node node;
        node["major"] = config.major;
        node["minor"] = config.minor;

        return node;
    }

    static bool decode(const Node& node, BlueDwarf::configuration::OpenGLVersion& config) {
        if(!node.IsMap()) {
            throw DWARF_EXCEPTION("rendering.opengl.version has to be a map");
        }

        if(!node["major"].IsScalar()) {
            throw DWARF_EXCEPTION("rendering.opengl.version.major has to be an integer");
        }

        if(!node["minor"].IsScalar()) {
            throw DWARF_EXCEPTION("rendering.opengl.version.minor has to be an integer");
        }

        config.major = node["major"].as<int>();
        config.minor = node["minor"].as<int>();

        return true;
    }
};

template<> struct BD_API_EXPORT convert<BlueDwarf::configuration::OpenGLConfig> {
    static Node encode(const BlueDwarf::configuration::OpenGLConfig& config) {
        Node node;
        node["version"] = config.version;

        return node;
    }

    static bool decode(const Node& node, BlueDwarf::configuration::OpenGLConfig& config) {
        if(!node.IsMap()) {
            throw DWARF_EXCEPTION("rendering.opengl has to be a map");
        }

        if(!node["version"].IsDefined()) {
            throw DWARF_EXCEPTION("rendering.opengl.version has to be set");
        }

        config.version = node["version"].as<BlueDwarf::configuration::OpenGLVersion>();

        return true;
    }
};

template<> struct BD_API_EXPORT convert<BlueDwarf::configuration::RenderingConfig> {
    static Node encode(const BlueDwarf::configuration::RenderingConfig& config) {
        Node node;
        node["window"] = config.window;
        node["opengl"] = config.opengl;

        return node;
    }

    static bool decode(const Node& node, BlueDwarf::configuration::RenderingConfig& config) {
        if(!node.IsMap()) {
            throw DWARF_EXCEPTION("rendering has to be a map");
        }

        if(!node["window"].IsDefined()) {
            throw DWARF_EXCEPTION("rendering.window has to be set");
        }

        if(!node["opengl"].IsDefined()) {
            throw DWARF_EXCEPTION("rendering.opengl has to be set");
        }

        config.window = node["window"].as<BlueDwarf::configuration::WindowConfig>();
        config.opengl = node["opengl"].as<BlueDwarf::configuration::OpenGLConfig>();

        return true;
    }
};

template<> struct BD_API_EXPORT convert<BlueDwarf::configuration::EngineConfig> {
    static Node encode(const BlueDwarf::configuration::EngineConfig& config) {
        Node node;
        node["load-native-extensions"] = config.loadNativeExtensions;

        return node;
    }

    static bool decode(const Node& node, BlueDwarf::configuration::EngineConfig& config) {
        if(!node.IsMap()) {
            throw DWARF_EXCEPTION("engine has to be a map");
        }

        if(!node["load-native-extensions"].IsScalar()) {
            throw DWARF_EXCEPTION("engine.load-native-extensions has to be a boolean");
        }

        config.loadNativeExtensions = node["load-native-extensions"].as<bool>();

        return true;
    }
};

template<> struct BD_API_EXPORT convert<BlueDwarf::Configuration> {
    static Node encode(const BlueDwarf::Configuration& config) {
        Node node;
        node["rendering"] = config.rendering;
        node["engine"] = config.engine;

        return node;
    }

    static bool decode(const Node& node, BlueDwarf::Configuration& config) {
        if(!node.IsMap()) {
            throw DWARF_EXCEPTION("YAML config root has to be a map");
        }

        if(!node["rendering"].IsDefined()) {
            throw DWARF_EXCEPTION("rendering has to be set");
        }

        if(!node["engine"].IsDefined()) {
            throw DWARF_EXCEPTION("engine has to be set");
        }

        config.rendering = node["rendering"].as<BlueDwarf::configuration::RenderingConfig>();
        config.engine = node["engine"].as<BlueDwarf::configuration::EngineConfig>();

        return true;
    }
};
}