#include "glove/log/Message.hpp"

namespace BlueDwarf {
std::ostream& operator<<(std::ostream& stream, const LogLevel& logLevel) {
    static std::string logLevels[] = {"ERROR", " WARN", " INFO", "DEBUG", "TRACE"};

    stream << logLevels[static_cast<int>(logLevel)];
    return stream;
}
}