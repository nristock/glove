#pragma once

#include <string>

#include "glove/GloveApi.hpp"
#include "glove/Version.hpp"
#include "glove/natex/Module.hpp"

namespace glove {

class GLOVE_API_EXPORT BasicModule : public Module {
  public:
    BasicModule(const std::string& name, ModuleVersionInfo moduleVersionInfo);

    virtual const std::string& GetName() const override;
    virtual const ModuleVersionInfo& GetVersion() const override;

  protected:
    std::string name;
    ModuleVersionInfo version;
};

} /* namespace glove */