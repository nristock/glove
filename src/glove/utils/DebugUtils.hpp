#pragma once

#include <boost/format.hpp>

#include "glove/GloveConfig.hpp"
#include "glove/log/Log.hpp"

#if BD_DEBUG_BREAK
#include <csignal>
#endif

namespace BlueDwarf {
namespace debug {
inline bool _DebugAssert(const char* file, int line, const char* expression, bool assertionResult) {
    if (assertionResult) {
        return assertionResult;
    }

    L_DEBUG(fmt::format("Debug assertion failed in {0}:{1}: {2}", file, line, expression));

#if BD_DEBUG_BREAK
#if defined(ON_UNIX)
        L_DEBUG("Sending SIGSTOP: Attach debugger now");
        raise(SIGSTOP);
#else
        raise(SIGABRT);
#endif
#endif

    return assertionResult;
}

inline bool _Check(const char* file, int line, const char* expression, bool assertionResult) {
#if BD_TREAT_CHECK_AS_ASSERTION
    return _DebugAssert(file, line, expression, assertionResult);
#else
    if (assertionResult) {
        return assertionResult;
    }

    L_DEBUG(fmt::format("Debug check failed in {0}:{1}: {2}", file, line, expression));
#endif

    return assertionResult;
}
}
}

#if defined(BD_DEBUG_BUILD)
/// \brief DebugAssert will print a debug message if expr is false and trigger a debug break if BD_DEBUG_BREAK is set
/// Invokes BlueDwarf::debug::_DebugAssert
#define DebugAssert(expr) BlueDwarf::debug::_DebugAssert(__FILE__, __LINE__, #expr, expr)

/// \brief Check will print a debug message if expr is false. If BD_TREAT_CHECK_AS_ASSERTION is set Check is equal to DebugAssert
/// Invokes BlueDwarf::debug::_Check
#define Check(expr) BlueDwarf::debug::_Check(__FILE__, __LINE__, #expr, expr)
#else
#define DebugAssert(expr) expr
#define Check(expr) expr
#endif