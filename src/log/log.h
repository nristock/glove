#ifndef _LOG_H_INCLUDED
#define _LOG_H_INCLUDED

#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/thread/shared_mutex.hpp>

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

    typedef boost::log::attributes::mutable_constant<
    	    int,
    	    boost::shared_mutex,
    	    boost::unique_lock< boost::shared_mutex >,
    	    boost::shared_lock< boost::shared_mutex >
    	> MutableIntMT;
    typedef boost::log::attributes::mutable_constant<
    	    std::string,
    	    boost::shared_mutex,
    	    boost::unique_lock< boost::shared_mutex >,
    	    boost::shared_lock< boost::shared_mutex >
    	> MutableStringMT;

    typedef boost::log::sources::severity_logger<SeverityLevel> GloveLogger;

    extern MutableStringMT fileAttr;
    extern MutableStringMT functionAttr;
    extern MutableIntMT lineAttr;

    extern GloveLogger globalLogger;

    template<typename T> static inline T& TagLogMessage
        (T &log_,
         const std::string file_,
         int line_,
         const std::string function_) {
        fileAttr.set(file_);
        functionAttr.set(function_);
        lineAttr.set(line_);
        return log_;
    }

    void InitLoggingSystem();
}

#define LOG(log_, lvl_) BOOST_LOG_SEV(glove::logging::TagLogMessage(log_, __FILE__, __LINE__, __func__), glove::logging::SeverityLevel::lvl_)

}

#endif
