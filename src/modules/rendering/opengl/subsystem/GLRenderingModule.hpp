#pragma once

#include <glove/natex/Natex.hpp>

namespace glove {
namespace gl {
class GLRenderingModule : public Module {
  public:
    virtual void Load();
    virtual void Unload();
    virtual void RegisterServices(ServiceRegistry& serviceRegistry);
    virtual const std::string& GetName() const;
    virtual const ModuleVersionInfo& GetVersion() const;
};
}
}