#pragma once

#include <memory>

namespace glove {

struct GloveEnvironment {
std::string executablePath;

    std::string MakeDataPath(std::string const& relPath) const;
};

typedef std::shared_ptr<GloveEnvironment> GloveEnvironmentPtr;

extern GloveEnvironmentPtr gEnv;

}