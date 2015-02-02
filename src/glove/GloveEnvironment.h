#pragma once

#include <string>
#include <memory>
#include <map>

#include "glove/configuration/Configuration.hpp"

namespace glove {

struct GloveEnvironment {
    std::string executablePath;
    std::string executableName;

    Configuration engineConfiguration;

    std::string MakeDataPath(std::string const& relPath) const;
};

typedef std::shared_ptr<GloveEnvironment> GloveEnvironmentPtr;

extern GloveEnvironmentPtr gEnv;
}