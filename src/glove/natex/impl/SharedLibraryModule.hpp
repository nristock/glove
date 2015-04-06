#pragma once

#include "glove/GloveApi.hpp"
#include "glove/natex/Module.hpp"
#include "glove/natex/SharedLibrary.hpp"

namespace glove {
/// \brief Module decorator/pimpl class used to couple shared libraries to modules.
///
/// A SharedLibraryModule forwards all method calls to the implementation pointer which is a Module instance created
/// in a DSO.
class GLOVE_API_EXPORT SharedLibraryModule : public Module {
  public:
    SharedLibraryModule(std::unique_ptr<Module> implementation, std::unique_ptr<SharedLibrary> dso);

    virtual void Load();
    virtual void Unload();
    virtual void RegisterServices(ServiceRegistry& serviceRegistry);
    virtual const std::string& GetName() const;
    virtual const ModuleVersionInfo& GetVersion() const;

  private:
    std::unique_ptr<Module> implementation;
    std::unique_ptr<SharedLibrary> dso;
};
}