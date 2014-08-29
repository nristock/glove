#ifndef _LOG_H_INCLUDED
#define _LOG_H_INCLUDED

#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/attributes/named_scope.hpp>

namespace glove {
namespace logging {
	enum SeverityLevel {
		debug,
		info,
		warning,
		error,
		fatal
	};

	std::ostream& operator<< (std::ostream& strm, SeverityLevel level);
	
	typedef boost::log::sources::wseverity_logger<SeverityLevel> GloveLogger;
	extern GloveLogger globalLogger;

    void InitLoggingSystem();
}

#define LOG(log_, lvl_, lgs_) {BOOST_LOG_FUNCTION(); BOOST_LOG_SEV(log_, glove::logging::SeverityLevel::lvl_) << lgs_;}

}

#endif
