#include <vendor/gtest/gtest.h>

#include <random>

#include <yaml-cpp/yaml.h>

#include "core/configuration/Configuration.hpp"
#include "core/configuration/ConfigurationConverters.hpp"

using ::glove::configuration::WindowConfig;
using ::glove::configuration::OpenGLVersion;
using ::glove::configuration::OpenGLConfig;
using ::glove::configuration::RenderingConfig;
using ::glove::configuration::EngineConfig;
using ::glove::Configuration;

namespace glove {

class ConfigurationTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(1, 400);

        expectedConfig.rendering.window.width = distribution(generator);
        expectedConfig.rendering.window.height = distribution(generator);
        expectedConfig.rendering.opengl.version.major = distribution(generator);
        expectedConfig.rendering.opengl.version.minor = distribution(generator);
        expectedConfig.engine.loadNativeExtensions = distribution(generator) % 2 == 0;

        windowConfigNode["width"] = expectedConfig.rendering.window.width;
        windowConfigNode["height"] = expectedConfig.rendering.window.height;

        openGlVersionNode["major"] = expectedConfig.rendering.opengl.version.major;
        openGlVersionNode["minor"] = expectedConfig.rendering.opengl.version.minor;

        openGlConfigNode["version"] = openGlVersionNode;

        renderingConfigNode["window"] = windowConfigNode;
        renderingConfigNode["opengl"] = openGlConfigNode;

        engineConfigNode["load-native-extensions"] = expectedConfig.engine.loadNativeExtensions;

        configurationRootNode["rendering"] = renderingConfigNode;
        configurationRootNode["engine"] = engineConfigNode;
    }

    YAML::Node windowConfigNode;
    YAML::Node openGlVersionNode;
    YAML::Node openGlConfigNode;
    YAML::Node renderingConfigNode;
    YAML::Node engineConfigNode;
    YAML::Node configurationRootNode;

    Configuration expectedConfig;
};

TEST_F(ConfigurationTest, CanDeserializeWindowConfigFromNode) {
    WindowConfig windowConfig = windowConfigNode.as<WindowConfig>();

    EXPECT_EQ(expectedConfig.rendering.window.width, windowConfig.width);
    EXPECT_EQ(expectedConfig.rendering.window.height, windowConfig.height);
}

TEST_F(ConfigurationTest, CanDeserializeOpenGLVersionFromNode) {
    OpenGLVersion openGLVersion = openGlVersionNode.as<OpenGLVersion>();

    EXPECT_EQ(expectedConfig.rendering.opengl.version.major, openGLVersion.major);
    EXPECT_EQ(expectedConfig.rendering.opengl.version.minor, openGLVersion.minor);
}

TEST_F(ConfigurationTest, CanDeserializeOpenGLConfigFromNode) {
    OpenGLConfig openGLConfig = openGlConfigNode.as<OpenGLConfig>();

    EXPECT_EQ(expectedConfig.rendering.opengl.version.major, openGLConfig.version.major);
    EXPECT_EQ(expectedConfig.rendering.opengl.version.minor, openGLConfig.version.minor);
}

TEST_F(ConfigurationTest, CanDeserializeRenderingConfigFromNode) {
    RenderingConfig renderingConfig = renderingConfigNode.as<RenderingConfig>();

    EXPECT_EQ(expectedConfig.rendering.window.width, renderingConfig.window.width);
    EXPECT_EQ(expectedConfig.rendering.window.height, renderingConfig.window.height);

    EXPECT_EQ(expectedConfig.rendering.opengl.version.major, renderingConfig.opengl.version.major);
    EXPECT_EQ(expectedConfig.rendering.opengl.version.minor, renderingConfig.opengl.version.minor);
}

TEST_F(ConfigurationTest, CanDeserializeEngineConfigFromNode) {
    EngineConfig engineConfig = engineConfigNode.as<EngineConfig>();

    EXPECT_EQ(expectedConfig.engine.loadNativeExtensions, engineConfig.loadNativeExtensions);
}

TEST_F(ConfigurationTest, CanDeserializeConfigurationFromNode) {
    Configuration config = configurationRootNode.as<Configuration>();

    EXPECT_EQ(expectedConfig.rendering.window.width, config.rendering.window.width);
    EXPECT_EQ(expectedConfig.rendering.window.height, config.rendering.window.height);

    EXPECT_EQ(expectedConfig.rendering.opengl.version.major, config.rendering.opengl.version.major);
    EXPECT_EQ(expectedConfig.rendering.opengl.version.minor, config.rendering.opengl.version.minor);

    EXPECT_EQ(expectedConfig.engine.loadNativeExtensions, config.engine.loadNativeExtensions);
}

TEST_F(ConfigurationTest, CanSerializeWindowConfigToNode) {
    YAML::Node testNode(expectedConfig.rendering.window);

    EXPECT_EQ(expectedConfig.rendering.window.width, windowConfigNode["width"].as<int>());
    EXPECT_EQ(expectedConfig.rendering.window.height, windowConfigNode["height"].as<int>());
}

TEST_F(ConfigurationTest, CanSerializeOpenGLVersionToNode) {
    YAML::Node testNode(expectedConfig.rendering.opengl.version);

    EXPECT_EQ(expectedConfig.rendering.opengl.version.major, openGlVersionNode["major"].as<int>());
    EXPECT_EQ(expectedConfig.rendering.opengl.version.minor, openGlVersionNode["minor"].as<int>());
}

TEST_F(ConfigurationTest, CanSerializeOpenGLConfigToNode) {
    YAML::Node testNode(expectedConfig.rendering.opengl);

    EXPECT_EQ(expectedConfig.rendering.opengl.version.major, openGlConfigNode["version"]["major"].as<int>());
    EXPECT_EQ(expectedConfig.rendering.opengl.version.minor, openGlConfigNode["version"]["minor"].as<int>());
}

TEST_F(ConfigurationTest, CanSerializeRenderingConfigToNode) {
    YAML::Node testNode(expectedConfig.rendering);

    EXPECT_EQ(expectedConfig.rendering.opengl.version.major, testNode["opengl"]["version"]["major"].as<int>());
    EXPECT_EQ(expectedConfig.rendering.opengl.version.minor, testNode["opengl"]["version"]["minor"].as<int>());

    EXPECT_EQ(expectedConfig.rendering.window.width, testNode["window"]["width"].as<int>());
    EXPECT_EQ(expectedConfig.rendering.window.height, testNode["window"]["height"].as<int>());
}

TEST_F(ConfigurationTest, CanSerializeEngineConfigToNode) {
    YAML::Node testNode(expectedConfig.engine);

    EXPECT_EQ(expectedConfig.engine.loadNativeExtensions, testNode["load-native-extensions"].as<bool>());
}

TEST_F(ConfigurationTest, CanSerializeConfigurationToNode) {
    YAML::Node testNode(expectedConfig);

    EXPECT_EQ(expectedConfig.rendering.opengl.version.major, testNode["rendering"]["opengl"]["version"]["major"].as<int>());
    EXPECT_EQ(expectedConfig.rendering.opengl.version.minor, testNode["rendering"]["opengl"]["version"]["minor"].as<int>());

    EXPECT_EQ(expectedConfig.rendering.window.width, testNode["rendering"]["window"]["width"].as<int>());
    EXPECT_EQ(expectedConfig.rendering.window.height, testNode["rendering"]["window"]["height"].as<int>());

    EXPECT_EQ(expectedConfig.engine.loadNativeExtensions, testNode["engine"]["load-native-extensions"].as<bool>());
}

}