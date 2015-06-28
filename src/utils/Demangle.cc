#include "Demangle.hpp"

// include a std header here so we can get std lib defines
#include <string>
#if defined(__GLIBCXX__) || defined(__GLIBCPP__)
#define BD_USE_DEMANGLE 1
#include <cxxabi.h>
#elif defined(__clang__) && defined(__has_include)
#if __has_include(<cxxabi.h>)
#define BD_USE_DEMANGLE 1
#include <cxxabi.h>
#endif
#endif

namespace BlueDwarf {

const char* Demangle(const char* mangledString) {
#if defined(BD_USE_DEMANGLE)
    return __cxxabiv1::__cxa_demangle(mangledString, nullptr, 0, nullptr);
    #else
    return mangledString;
#endif
}

}