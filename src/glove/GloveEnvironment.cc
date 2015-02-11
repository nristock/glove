#include <boost/format.hpp>

#include "glove/GloveEnvironment.hpp"

namespace glove {

GloveEnvironmentPtr gEnv;

std::string GloveEnvironment::MakeDataPath(const std::string& relPath) const {
    return (boost::format("%1%/%2%") % executablePath % relPath).str();
}
}