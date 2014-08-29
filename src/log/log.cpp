#include "log.h"

#include <fstream>
#include <iomanip>

// TODO: remove unused headers
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/named_scope.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>

namespace blogging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;
namespace attr = boost::log::attributes;

namespace glove {
namespace logging {
GloveLogger globalLogger;

void InitLoggingSystem() {
	blogging::add_common_attributes();

	typedef sinks::synchronous_sink<sinks::text_ostream_backend> textSink;
	boost::shared_ptr<textSink> sink = boost::make_shared<textSink>();

	sink->locked_backend()->add_stream(
		boost::make_shared<std::ofstream>("glove.log"));

	boost::shared_ptr<std::ostream> clogStream(&std::clog,
		boost::null_deleter());
	sink->locked_backend()->add_stream(clogStream);

	sink->set_formatter(
		expr::stream
		<< L"[" << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%H:%M:%S") << L" "
		<< expr::attr<SeverityLevel>("Severity") << L" "
		<< expr::attr<blogging::thread_id>("ThreadID") << L" "
		<< expr::format_named_scope("Scopes", keywords::format = "(%C %F:%l)", keywords::depth = 3)
		<< L"]" << std::endl << expr::message << std::endl);

	auto core = blogging::core::get();
	core->add_global_attribute("Scopes", attr::named_scope());

	core->add_sink(sink);
}

std::ostream& operator<< (std::ostream& strm, SeverityLevel level)
{
	static const char* strings[] =
	{
		"DEBUG",
		"INFO ",
		"WARN ",
		"ERROR",
		"FATAL"
	};

	if (static_cast<std::size_t>(level) < sizeof(strings) / sizeof(*strings))
		strm << strings[level];
	else
		strm << static_cast<int>(level);

	return strm;
}

}
}

