#pragma once

#include <list>

#include "glove/BlueDwarfFwd.hpp"
#include "glove/log/Log.hpp"
#include "glove/configuration/Configuration.hpp"
#include "glove/natex/Natex.hpp"

namespace BlueDwarf {

class BD_API_EXPORT DwarfCore : public std::enable_shared_from_this<DwarfCore> {
  public:
    DwarfCore(const Configuration& engineConfig, const ServiceRegistryHandle& serviceRegistry, const std::vector<ModuleHandle>& loadedModules);
    virtual ~DwarfCore() = default;

    DwarfCore(const DwarfCore&) = delete;
    DwarfCore& operator=(const DwarfCore&) = delete;

    const Configuration& GetConfig() const {return engineConfiguration; }
    const ServiceRegistryHandle& GetServiceRegistry() const {return serviceRegistry; }

  private:
    Configuration engineConfiguration;
    ServiceRegistryHandle serviceRegistry;
    std::vector<std::shared_ptr<Module>> loadedModules;

    Logger logger;

    friend class CoreBuilder;
};

} /* namespace BlueDwarf */
