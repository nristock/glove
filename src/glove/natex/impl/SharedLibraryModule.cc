#include "glove/utils/DebugUtils.hpp"
#include "glove/natex/impl/SharedLibraryModule.hpp"

namespace glove {

    SharedLibraryModule::SharedLibraryModule(std::unique_ptr<Module> implementation, std::unique_ptr<SharedLibrary> dso) : implementation(std::move(implementation)), dso(std::move(dso)) {
        DebugAssert((bool)this->implementation);
        DebugAssert((bool)this->dso);
    }

    void SharedLibraryModule::Load() {
        implementation->Load();
    }

    void SharedLibraryModule::Unload() {
        implementation->Unload();
    }

    void SharedLibraryModule::RegisterServices(ServiceRegistry& serviceRegistry) {
        implementation->RegisterServices(serviceRegistry);
    }

    const std::string& SharedLibraryModule::GetName() const {
        return implementation->GetName();
    }

    const ModuleVersionInfo& SharedLibraryModule::GetVersion() const {
        return implementation->GetVersion();
    }
}