#include "GloveEnvironment.h"

#include <boost/format.hpp>

namespace glove {

GloveEnvironmentPtr gEnv;

std::string GloveEnvironment::MakeDataPath(const std::string& relPath) const {
    return (boost::format("%1%/%2%") % executablePath % relPath).str();
}

}