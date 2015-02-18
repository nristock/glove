#define GLOVE_VERSION_MAJOR 1
#define GLOVE_VERSION_MINOR 0
#define GLOVE_VERSION_PATCH 0

#define GLOVE_VERSION_STRING "1.0.0"

#define GLOVE_GIT_BRANCH "master"
#define GLOVE_GIT_SHORT_HASH "b10902b"
#define GLOVE_GIT "master (b10902b)"

#if !defined(ON_WINDOWS)
/* #undef ON_WINDOWS */
#endif

#if !defined(ON_UNIX)
#define ON_UNIX
#endif

#if !defined(GLOVE_DEBUG_BUILD)
#define GLOVE_DEBUG_BUILD
#endif

#define GLOVE_SERVICES_EXPECTED_SERVICE_COUNT 10

#if !defined(GLOVE_DEBUG_BREAK)
#define GLOVE_DEBUG_BREAK
#endif

#if !defined(GLOVE_TREAT_CHECK_AS_ASSERTION)
/* #undef GLOVE_TREAT_CHECK_AS_ASSERTION */
#endif
