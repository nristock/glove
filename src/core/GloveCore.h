#pragma once

#include <chrono>
#include <list>

#include <core/log/Log.h>

#include "GloveFwd.h"

#include "GloveException.h"
#include "rendering/FrameData.h"
#include <core/BifrostLoader.h>

namespace glove {

class GloveCore : public std::enable_shared_from_this<GloveCore> {
    Profilable();

  public:
    GloveCore(int argc, const char** argv);

    virtual ~GloveCore();

    GloveCore(const GloveCore&) = delete;
    GloveCore& operator=(const GloveCore&) = delete;

    /** Initializes the Glove engine and all subsystems. Must be called from main thread. */
    void Init(int argc, const char** argv);

    /** Starts the main application loop. Must be called from main thread. */
    void EnterMainLoop();

    void Update();

    void Render(ScenegraphPointer scenegraph);

    const GlovePythonEnginePtr& GetPythonEngine() const { return pythonEngine; }

    const PyShedLoaderPtr& GetPyshedLoader() const { return pyshedLoader; }

    const RendererPtr& GetRenderer() const { return renderer; }

    const ScenegraphPtr& GetScenegraph() const { return primaryScenegraph; }

    //    const GpuBufferManagerPtr& GetGpuBufferManager() const { return gpuBufferManager; }

    const PluginLoaderPtr& GetPluginLoader() const { return pluginLoader; }

    const EventBusPtr& GetEventBus() const { return eventBus; }

    const InputManagerPtr& GetInputManager() const { return inputManager; }

    bool IsExitRequested() const { return exitRequested; }

    void SetExitRequested(bool requestExit) { exitRequested = requestExit; }

    void LoadConfiguration(const std::string& param);

  private:
    typedef std::chrono::steady_clock::time_point TimePoint;
    typedef std::list<ISystemExtensionPtr> SystemExtensionList;

    logging::GloveLogger logger;

    BifrostLoader bifrostLoader;

    EventBusPtr eventBus;
    RendererPtr renderer;
    GlovePythonEnginePtr pythonEngine;
    PyShedLoaderPtr pyshedLoader;
    //    GpuBufferManagerPtr gpuBufferManager;
    ScenegraphPtr primaryScenegraph;
    PluginLoaderPtr pluginLoader;
    InputManagerPtr inputManager;

    TimePoint initializationTime;

    std::chrono::duration<double> lastFrameTime;

    SystemExtensionList systemExtensionList;

    FrameData frameData;

    unsigned long frameCounter;
    bool exitRequested;

    void InitializeRenderingSystem(int windowWidth, int windowHeight);

    void InitializeScripting();

    void InitializeResourceLoaders();
};

} /* namespace glove */
