#pragma once

#include <chrono>
#include <list>

#include "glove/GloveFwd.hpp"
#include "glove/log/Log.hpp"
#include "glove/configuration/Configuration.hpp"
#include "glove/GloveException.hpp"
#include "glove/rendering/FrameData.hpp"
#include "glove/natex/BifrostLoader.hpp"
#include "glove/graph/Graph.hpp"
#include "glove/services/ServiceRegistry.hpp"

namespace glove {

class GLOVE_API_EXPORT GloveCore : public std::enable_shared_from_this<GloveCore> {
  public:
    GloveCore(const Configuration& engineConfig, const ServiceRegistryHandle& serviceRegistry, const std::vector<std::shared_ptr<Module>>& loadedModules);
    virtual ~GloveCore() = default;

    GloveCore(const GloveCore&) = delete;
    GloveCore& operator=(const GloveCore&) = delete;

    const Configuration& GetConfig() const {return engineConfiguration; }
    const ServiceRegistryHandle& GetServiceRegistry() const {return serviceRegistry; }

  private:
    typedef std::chrono::steady_clock::time_point TimePoint;

    Configuration engineConfiguration;
    ServiceRegistryHandle serviceRegistry;
    std::vector<std::shared_ptr<Module>> loadedModules;

    logging::GloveLogger logger;

    friend class CoreBuilder;
};

} /* namespace glove */
