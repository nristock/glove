#include "glove/natex/Module.hpp"

namespace BlueDwarf {

ModuleVersionInfo::ModuleVersionInfo(ushort majorVersion, ushort minorVersion, ushort patchVersion) : VersionInfo(majorVersion, minorVersion, patchVersion){

}

bool ModuleVersionInfo::IsCompatibleWith(const EngineVersionInfo& engineVersion) const {
    return true;
}

bool ModuleVersionInfo::operator==(const ModuleVersionInfo& rhs) const {
    return VersionInfo::operator==(rhs);
}
}