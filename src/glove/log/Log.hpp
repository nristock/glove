#pragma once

#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include "glove/GloveApi.hpp"

namespace glove {
namespace logging {
enum GLOVE_API_EXPORT SeverityLevel { debug, info, warning, error, fatal };

std::ostream& GLOVE_API_EXPORT operator<<(std::ostream& strm, SeverityLevel level);

typedef boost::log::sources::wseverity_logger<SeverityLevel> GloveLogger;
extern GLOVE_API_EXPORT GloveLogger globalLogger;

void InitLoggingSystem();
}

#define LOG(log_, lvl_, lgs_)                                                                                          \
    {                                                                                                                  \
        BOOST_LOG_FUNCTION();                                                                                          \
        BOOST_LOG_SEV(log_, glove::logging::SeverityLevel::lvl_) << lgs_;                                              \
    }
}
