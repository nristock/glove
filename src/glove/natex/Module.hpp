#pragma once

#include <string>

#include "glove/BlueDwarfApi.hpp"
#include "glove/Version.hpp"
#include "glove/services/ServiceRegistry.hpp"

namespace BlueDwarf {

class ModuleVersionInfo : public VersionInfo {
  public:
    ModuleVersionInfo(ushort majorVersion, ushort minorVersion, ushort patchVersion);

    virtual bool IsCompatibleWith(const EngineVersionInfo& engineVersion) const;

    bool operator==(const ModuleVersionInfo& rhs) const;
};

/// \brief Module interface class.
class BD_API_EXPORT Module {
  public:
    virtual ~Module() = default;

    virtual void Load() = 0;
    virtual void Unload() = 0;
    virtual void RegisterServices(ServiceRegistry& serviceRegistry) = 0;
    virtual const std::string& GetName() const = 0;
    virtual const ModuleVersionInfo& GetVersion() const = 0;
};

} /* namespace BlueDwarf */