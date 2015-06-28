#include "glove/natex/BasicModule.hpp"

namespace BlueDwarf {
BasicModule::BasicModule(const std::string& name, ModuleVersionInfo moduleVersionInfo) : name(name), version(moduleVersionInfo) {

}

const std::string& BasicModule::GetName() const {
    return name;
}

const ModuleVersionInfo& BasicModule::GetVersion() const {
    return version;
}
}