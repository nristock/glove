#pragma once

#include <vector>

#include <yaml-cpp/yaml.h>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {

namespace configuration {
struct BD_API_EXPORT WindowConfig {
    int width;
    int height;
};

struct BD_API_EXPORT OpenGLVersion {
    int major;
    int minor;
};

struct BD_API_EXPORT OpenGLConfig {
    OpenGLVersion version;
};

struct BD_API_EXPORT RenderingConfig {
    WindowConfig window;
    OpenGLConfig opengl;
};

struct BD_API_EXPORT EngineConfig {
    bool loadNativeExtensions;
};
}

class BD_API_EXPORT Configuration {
  public:
    Configuration() = default;
    virtual ~Configuration() = default;

    static Configuration LoadFromFile(const std::string& filePath);
    void SaveToFile(const std::string& path);

    void LoadDefaults();

    configuration::RenderingConfig rendering;
    configuration::EngineConfig engine;

    YAML::Node configurationRoot;
};
}