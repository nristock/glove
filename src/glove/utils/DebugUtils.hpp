#pragma once

#include <boost/format.hpp>

#include "glove/GloveConfig.hpp"
#include "glove/log/Log.hpp"

#if GLOVE_DEBUG_BREAK
#include <csignal>
#endif

namespace glove {
namespace debug {
inline bool _DebugAssert(const char* file, int line, const char* expression, bool assertionResult) {
    if (assertionResult) {
        return assertionResult;
    }

    LOG(logging::globalLogger, debug,
        (boost::format("Debug assertion failed in %1%:%2%: %3%") % file % line % expression).str());

    if (GLOVE_DEBUG_BREAK) {
#if defined(ON_UNIX)
        LOG(logging::globalLogger, debug, "Sending SIGSTOP: Attach debugger now");
        raise(SIGSTOP);
#else
        raise(SIGABRT);
#endif
    }

    return assertionResult;
}

inline bool _Check(const char* file, int line, const char* expression, bool assertionResult) {
#if GLOVE_TREAT_CHECK_AS_ASSERTION
    return _DebugAssert(file, line, expression, assertionResult);
#else
    if (assertionResult) {
        return assertionResult;
    }

    LOG(logging::globalLogger, debug,
        (boost::format("Debug check failed in %1%:%2%: %3%") % file % line % expression).str());
#endif

    return assertionResult;
}
}
}

#if defined(GLOVE_DEBUG_BUILD)
/// \brief DebugAssert will print a debug message if expr is false and trigger a debug break if GLOVE_DEBUG_BREAK is set
/// Invokes glove::debug::_DebugAssert
#define DebugAssert(expr) glove::debug::_DebugAssert(__FILE__, __LINE__, #expr, expr)

/// \brief Check will print a debug message if expr is false. If GLOVE_TREAT_CHECK_AS_ASSERTION is set Check is equal to DebugAssert
/// Invokes glove::debug::_Check
#define Check(expr) glove::debug::_Check(__FILE__, __LINE__, #expr, expr)
#else
#define DebugAssert(expr) expr
#define Check(expr) expr
#endif