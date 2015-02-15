#pragma once

#include <chrono>
#include <list>
#include <glove/natex/ISubsystemInstanceRegistry.hpp>

#include "glove/GloveFwd.hpp"
#include "glove/log/Log.hpp"
#include "glove/configuration/Configuration.hpp"
#include "glove/GloveException.hpp"
#include "glove/rendering/FrameData.hpp"
#include "glove/natex/BifrostLoader.hpp"
#include "glove/graph/Graph.hpp"
#include "glove/natex/GloveSubsystemInstanceRegistry.hpp"
#include "glove/natex/ISubsystem.hpp"

namespace glove {

class GLOVE_API_EXPORT GloveCore : public std::enable_shared_from_this<GloveCore> {
  public:
    GloveCore(const Configuration& engineConfig, const EventBusPtr& eventBus, const InputManagerPtr& inputManager,
              const ISubsystemInstanceRegistryPtr& subsystemInstanceRegistry,
              const ISystemExtensionLoaderHandle& systemExtensionLoader);
    virtual ~GloveCore() = default;

    GloveCore(const GloveCore&) = delete;
    GloveCore& operator=(const GloveCore&) = delete;

    const EventBusPtr& GetEventBus() const { return eventBus; }
    const InputManagerPtr& GetInputManager() const { return inputManager; }
    const ISubsystemInstanceRegistryPtr& GetSubsystemInstanceRegistry() const { return subsystemInstanceRegistry; }
    const Configuration& GetConfig() const {return engineConfiguration; }

    template <class T> std::shared_ptr<T> GetUniqueSubsystem() {
        ISubsystemPtr subsystem = subsystemInstanceRegistry->GetUniqueSubsystemOfType(T::subsystemType);
        return std::dynamic_pointer_cast<T>(subsystem);
    }

  private:
    typedef std::chrono::steady_clock::time_point TimePoint;

    Configuration engineConfiguration;
    EventBusPtr eventBus;
    InputManagerPtr inputManager;
    ISubsystemInstanceRegistryPtr subsystemInstanceRegistry;
    ISystemExtensionLoaderHandle systemExtensionLoader;

    logging::GloveLogger logger;

    friend class CoreBuilder;
};

} /* namespace glove */
