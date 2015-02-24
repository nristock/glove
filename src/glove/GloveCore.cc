#include <zlib.h>
#include <png.h>
#include <boost/version.hpp>

#include "glove/natex/Natex.hpp"
#include "glove/GloveConfig.hpp"

#include "glove/GloveCore.hpp"

namespace glove {

GloveCore::GloveCore(const Configuration& engineConfig, const ServiceRegistryHandle& serviceRegistry,
                     const std::vector<ModuleHandle>& loadedModules)
    : engineConfiguration(engineConfig), serviceRegistry(serviceRegistry), loadedModules(loadedModules) {
    LOG(logger, info, (boost::format("Creating GloveCore version %1%") % GLOVE_VERSION_STRING).str());

    LOG(logger, info, "Using ZLIB " << ZLIB_VERSION);
    LOG(logger, info, "Using libPng " << PNG_LIBPNG_VER_STRING);
    LOG(logger, info, "Using Boost " << (BOOST_VERSION / 100000) << "." << ((BOOST_VERSION / 100) % 1000) << "."
                                     << (BOOST_VERSION % 100));
}
} /* namespace glove */
