#pragma once

#include <glove/GloveFwd.hpp>
#include <glove/natex/ISystemExtension.h>

namespace glove {

class TestExtension : public ISystemExtension {

public:

    virtual ~TestExtension();

    virtual void RegisterSubsystems(const GloveCorePtr& engineCore);

    virtual const ExtensionUuid GetExtensionUuid() const;

    virtual const std::string& GetExtensionName() const;


    virtual void RegisterSubsystems(const ISubsystemDefinitionRegistryPtr& subsystemRegistry);
};

} /* namespace glove */