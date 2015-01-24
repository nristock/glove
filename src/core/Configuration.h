#pragma once

#include <vector>

#include "GloveException.h"

namespace glove {

namespace configuration {
struct WindowConfig {
    int width;
    int height;
};

struct OpenGLConfig {
    int versionMajor;
    int versionMinor;
};

struct RenderingConfig {
    WindowConfig window;
    OpenGLConfig opengl;
};

struct EngineConfig {
    bool loadNativeExtensions;
    std::vector<std::string> subsystemInitList;
};
}

class Configuration {
  public:
    Configuration() = default;
    virtual ~Configuration() = default;

    void LoadFromFile(const std::string& filePath);
    void SaveToFile(const std::string& path);

    void LoadDefaults();

    configuration::RenderingConfig rendering;
    configuration::EngineConfig engine;
};
}