#pragma once

#include <chrono>

#include <boost/program_options.hpp>
#include <log/Log.h>

#include "GloveFwd.h"

#include "GloveException.h"
#include "rendering/FrameData.h"

namespace glove {

class GloveCore : public std::enable_shared_from_this<GloveCore> {
Profilable();
public:
    GloveCore();

    virtual ~GloveCore();

    GloveCore(const GloveCore&) = delete;
    GloveCore& operator= (const GloveCore&) = delete;

    /** Initializes the Glove engine and all subsystems. Must be called from main thread. */
    void Init(int argc, char** argv);

    /** Starts the main application loop. Must be called from main thread. */
    void EnterMainLoop();

    void Update();

    void Render(ScenegraphPointer scenegraph);

    const GlovePythonEnginePtr& GetPythonEngine() const {return pythonEngine;}

    const PyShedLoaderPtr& GetPyshedLoader() const {return pyshedLoader;}

    const RendererPtr& GetRenderer() const {return renderer;}

    const ScenegraphPtr& GetScenegraph() const {return primaryScenegraph;}

    const GpuBufferManagerPtr& GetGpuBufferManager() const {return gpuBufferManager;}

    const PluginLoaderPtr& GetPluginLoader() const {return pluginLoader;}

    const EventBusPtr& GetEventBus() const {return eventBus;}

    const InputManagerPtr& GetInputManager() const {return inputManager;}

    bool IsExitRequested() const {return exitRequested;}

    void SetExitRequested(bool requestExit) {exitRequested = requestExit;}

private:
    typedef std::chrono::steady_clock::time_point TimePoint;

    logging::GloveLogger logger;

    EventBusPtr eventBus;
    RendererPtr renderer;
    GlovePythonEnginePtr pythonEngine;
    PyShedLoaderPtr pyshedLoader;
    GpuBufferManagerPtr gpuBufferManager;
    ScenegraphPtr primaryScenegraph;
    PluginLoaderPtr pluginLoader;
    InputManagerPtr inputManager;

    TimePoint initializationTime;

    std::chrono::duration<double> lastFrameTime;

    FrameData frameData;

    std::string executableName;
    std::string executablePath;

    boost::program_options::variables_map parsedArguments;

    unsigned long frameCounter;
    bool exitRequested;

    void InitializeRenderingSystem(int windowWidth, int windowHeight);

    void InitializeScripting();

    void InitializeResourceLoaders();
};

} /* namespace glove */
