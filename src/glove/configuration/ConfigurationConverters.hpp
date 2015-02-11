#pragma once

#include <yaml-cpp/yaml.h>

#include "glove/GloveException.h"
#include "glove/configuration/Configuration.hpp"

namespace YAML {
template<> struct convert<glove::configuration::WindowConfig> {
    static Node encode(const glove::configuration::WindowConfig& config) {
        Node node;
        node["width"] = config.width;
        node["height"] = config.height;

        return node;
    }

    static bool decode(const Node& node, glove::configuration::WindowConfig& config) {
        if(!node.IsMap()) {
            throw GLOVE_EXCEPTION("rendering.window has to be a map");
        }

        if(!node["width"].IsScalar()) {
            throw GLOVE_EXCEPTION("rendering.window.width has to be an integer");
        }

        if(!node["height"].IsScalar()) {
            throw GLOVE_EXCEPTION("rendering.window.height has to be an integer");
        }

        config.width = node["width"].as<int>();
        config.height = node["height"].as<int>();

        return true;
    }
};

template<> struct convert<glove::configuration::OpenGLVersion> {
    static Node encode(const glove::configuration::OpenGLVersion& config) {
        Node node;
        node["major"] = config.major;
        node["minor"] = config.minor;

        return node;
    }

    static bool decode(const Node& node, glove::configuration::OpenGLVersion& config) {
        if(!node.IsMap()) {
            throw GLOVE_EXCEPTION("rendering.opengl.version has to be a map");
        }

        if(!node["major"].IsScalar()) {
            throw GLOVE_EXCEPTION("rendering.opengl.version.major has to be an integer");
        }

        if(!node["minor"].IsScalar()) {
            throw GLOVE_EXCEPTION("rendering.opengl.version.minor has to be an integer");
        }

        config.major = node["major"].as<int>();
        config.minor = node["minor"].as<int>();

        return true;
    }
};

template<> struct convert<glove::configuration::OpenGLConfig> {
    static Node encode(const glove::configuration::OpenGLConfig& config) {
        Node node;
        node["version"] = config.version;

        return node;
    }

    static bool decode(const Node& node, glove::configuration::OpenGLConfig& config) {
        if(!node.IsMap()) {
            throw GLOVE_EXCEPTION("rendering.opengl has to be a map");
        }

        if(!node["version"].IsDefined()) {
            throw GLOVE_EXCEPTION("rendering.opengl.version has to be set");
        }

        config.version = node["version"].as<glove::configuration::OpenGLVersion>();

        return true;
    }
};

template<> struct convert<glove::configuration::RenderingConfig> {
    static Node encode(const glove::configuration::RenderingConfig& config) {
        Node node;
        node["window"] = config.window;
        node["opengl"] = config.opengl;

        return node;
    }

    static bool decode(const Node& node, glove::configuration::RenderingConfig& config) {
        if(!node.IsMap()) {
            throw GLOVE_EXCEPTION("rendering has to be a map");
        }

        if(!node["window"].IsDefined()) {
            throw GLOVE_EXCEPTION("rendering.window has to be set");
        }

        if(!node["opengl"].IsDefined()) {
            throw GLOVE_EXCEPTION("rendering.opengl has to be set");
        }

        config.window = node["window"].as<glove::configuration::WindowConfig>();
        config.opengl = node["opengl"].as<glove::configuration::OpenGLConfig>();

        return true;
    }
};

template<> struct convert<glove::configuration::EngineConfig> {
    static Node encode(const glove::configuration::EngineConfig& config) {
        Node node;
        node["load-native-extensions"] = config.loadNativeExtensions;

        return node;
    }

    static bool decode(const Node& node, glove::configuration::EngineConfig& config) {
        if(!node.IsMap()) {
            throw GLOVE_EXCEPTION("engine has to be a map");
        }

        if(!node["load-native-extensions"].IsScalar()) {
            throw GLOVE_EXCEPTION("engine.load-native-extensions has to be a boolean");
        }

        config.loadNativeExtensions = node["load-native-extensions"].as<bool>();

        return true;
    }
};

template<> struct convert<glove::Configuration> {
    static Node encode(const glove::Configuration& config) {
        Node node;
        node["rendering"] = config.rendering;
        node["engine"] = config.engine;

        return node;
    }

    static bool decode(const Node& node, glove::Configuration& config) {
        if(!node.IsMap()) {
            throw GLOVE_EXCEPTION("YAML config root has to be a map");
        }

        if(!node["rendering"].IsDefined()) {
            throw GLOVE_EXCEPTION("rendering has to be set");
        }

        if(!node["engine"].IsDefined()) {
            throw GLOVE_EXCEPTION("engine has to be set");
        }

        config.rendering = node["rendering"].as<glove::configuration::RenderingConfig>();
        config.engine = node["engine"].as<glove::configuration::EngineConfig>();

        return true;
    }
};
}