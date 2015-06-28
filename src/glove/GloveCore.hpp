#pragma once

#include <list>

#include "glove/GloveFwd.hpp"
#include "glove/log/Log.hpp"
#include "glove/configuration/Configuration.hpp"
#include "glove/natex/Natex.hpp"

namespace glove {

class GLOVE_API_EXPORT GloveCore : public std::enable_shared_from_this<GloveCore> {
  public:
    GloveCore(const Configuration& engineConfig, const ServiceRegistryHandle& serviceRegistry, const std::vector<ModuleHandle>& loadedModules);
    virtual ~GloveCore() = default;

    GloveCore(const GloveCore&) = delete;
    GloveCore& operator=(const GloveCore&) = delete;

    const Configuration& GetConfig() const {return engineConfiguration; }
    const ServiceRegistryHandle& GetServiceRegistry() const {return serviceRegistry; }

  private:
    Configuration engineConfiguration;
    ServiceRegistryHandle serviceRegistry;
    std::vector<std::shared_ptr<Module>> loadedModules;

    Logger logger;

    friend class CoreBuilder;
};

} /* namespace glove */
