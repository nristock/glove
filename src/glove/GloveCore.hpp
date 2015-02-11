#pragma once

#include <chrono>
#include <list>

#include "glove/GloveFwd.hpp"
#include "glove/log/Log.hpp"
#include "glove/GloveException.hpp"
#include "glove/rendering/FrameData.hpp"
#include "glove/natex/BifrostLoader.hpp"
#include "glove/graph/Graph.hpp"

namespace glove {

class GLOVE_API_EXPORT GloveCore : public std::enable_shared_from_this<GloveCore> {
  public:
    GloveCore(int argc, const char** argv);

    virtual ~GloveCore() = default;

    GloveCore(const GloveCore&) = delete;
    GloveCore& operator=(const GloveCore&) = delete;

    /** Initializes the Glove engine and all subsystems. Must be called from main thread. */
    void Init(int argc, const char** argv);

    /** Starts the main application loop. Must be called from main thread. */
    void EnterMainLoop(ScenegraphHandle scenegraph);

    void Update();

    virtual const EventBusPtr& GetEventBus() const { return eventBus; }

    const InputManagerPtr& GetInputManager() const { return inputManager; }

    bool IsExitRequested() const { return exitRequested; }

    void SetExitRequested(bool requestExit) { exitRequested = requestExit; }

    void LoadConfiguration(const std::string& param);

    const ISubsystemInstanceRegistryPtr& GetSubsystemInstanceRegistry() const { return subsystemInstanceRegistry; }

  private:
    typedef std::chrono::steady_clock::time_point TimePoint;
    typedef std::list<ISystemExtensionPtr> SystemExtensionList;

    logging::GloveLogger logger;

    BifrostLoader bifrostLoader;

    EventBusPtr eventBus;
    InputManagerPtr inputManager;

    ISubsystemInstanceRegistryPtr subsystemInstanceRegistry;

    TimePoint initializationTime;

    std::chrono::duration<double> lastFrameTime;

    FrameData frameData;

    unsigned long frameCounter;
    bool exitRequested;
};

} /* namespace glove */
