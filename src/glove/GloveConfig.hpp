#define BD_VERSION_MAJOR 1
#define BD_VERSION_MINOR 0
#define BD_VERSION_PATCH 0

#define BD_VERSION_STRING "1.0.0"

#define BD_GIT_BRANCH "master"
#define BD_GIT_SHORT_HASH "b10902b"
#define BD_GIT "master (b10902b)"

#define BD_POOL_WORKER_WAIT_TIMEOUT 500

#if !defined(ON_WINDOWS)
/* #undef ON_WINDOWS */
#endif

#if !defined(ON_UNIX)
#define ON_UNIX
#endif

#if !defined(BD_DEBUG_BUILD)
#define BD_DEBUG_BUILD
#endif

#define BD_SERVICES_EXPECTED_SERVICE_COUNT 10

#if !defined(BD_DEBUG_BREAK)
#define BD_DEBUG_BREAK
#endif

#if !defined(BD_TREAT_CHECK_AS_ASSERTION)
/* #undef BD_TREAT_CHECK_AS_ASSERTION */
#endif
