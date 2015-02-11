#pragma once

#include <string>
#include <memory>
#include <map>

#include "glove/GloveApi.hpp"
#include "glove/configuration/Configuration.hpp"

namespace glove {

struct GLOVE_API_EXPORT GloveEnvironment {
    std::string executablePath;
    std::string executableName;

    Configuration engineConfiguration;

    std::string MakeDataPath(std::string const& relPath) const;
};

typedef std::shared_ptr<GloveEnvironment> GloveEnvironmentPtr;

extern GLOVE_API_EXPORT GloveEnvironmentPtr gEnv;
}