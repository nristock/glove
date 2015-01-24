#pragma once

#include <vector>

#include <yaml-cpp/yaml.h>

#include "GloveException.h"

namespace glove {

namespace configuration {
struct WindowConfig {
    int width;
    int height;
};

struct OpenGLVersion {
    int major;
    int minor;
};

struct OpenGLConfig {
    OpenGLVersion version;
};

struct RenderingConfig {
    WindowConfig window;
    OpenGLConfig opengl;
};

struct EngineConfig {
    bool loadNativeExtensions;
};
}

class Configuration {
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