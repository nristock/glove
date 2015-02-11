#pragma once

#include <vector>

#include <yaml-cpp/yaml.h>

#include "glove/GloveApi.hpp"

namespace glove {

namespace configuration {
struct GLOVE_API_EXPORT WindowConfig {
    int width;
    int height;
};

struct GLOVE_API_EXPORT OpenGLVersion {
    int major;
    int minor;
};

struct GLOVE_API_EXPORT OpenGLConfig {
    OpenGLVersion version;
};

struct GLOVE_API_EXPORT RenderingConfig {
    WindowConfig window;
    OpenGLConfig opengl;
};

struct GLOVE_API_EXPORT EngineConfig {
    bool loadNativeExtensions;
};
}

class GLOVE_API_EXPORT Configuration {
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