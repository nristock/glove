#pragma once

#include <boost/format.hpp>

#include "glove/CommonTypes.hpp"

namespace glove {

class VersionInfo {
  public:
    VersionInfo(ushort majorVersion, ushort minorVersion, ushort patchVersion)
            : majorVersion(majorVersion), minorVersion(minorVersion), patchVersion(patchVersion) {}
    virtual ~VersionInfo() = default;

    virtual std::string ToString() const {
        return (boost::format("%1%.%2%.%3%") % majorVersion % minorVersion % patchVersion).str();
    }

    inline ushort const GetMajor() const {
        return majorVersion;
    }

    inline ushort const GetMinor() const {
        return minorVersion;
    }

    inline ushort const GetPatch() const {
        return patchVersion;
    }

    bool operator==(const VersionInfo& rhs) const {
        return majorVersion == rhs.majorVersion && minorVersion == rhs.minorVersion && patchVersion == rhs.patchVersion;
    }

  protected:
    const ushort majorVersion;
    const ushort minorVersion;
    const ushort patchVersion;
};

using EngineVersionInfo = VersionInfo;
}