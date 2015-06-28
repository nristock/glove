set(BD_VERSION_MAJOR 1)
set(BD_VERSION_MINOR 0)
set(BD_VERSION_PATCH 0)

option(BD_BUILD_TESTS "Whether to build tests or not" ON)
option(BD_BUILD_MODULES "Whether to build modules or not" ON)

##############################################
##############################################
include(GitInfo)

# General Configuration
if(WIN32)
	set(ON_WINDOWS 1)
	add_definitions(-DON_WINDOWS)
else()
	set(ON_UNIX 1)
	add_definitions(-DON_UNIX)
endif()

GetGitInfo(GIT_BRANCH GIT_SHORT_HASH)
message("On branch ${GIT_BRANCH} @ ${GIT_SHORT_HASH}")

set(BD_VERSION ${BD_VERSION_MAJOR}.${BD_VERSION_MINOR}.${BD_VERSION_PATCH})

set(BD_SERVICES_EXPECTED_SERVICE_COUNT 10)

set(BD_DEBUG_BREAK 1)
if(BD_DEBUG_BREAK)
add_definitions(-DBD_DEBUG_BREAK)
endif()

set(BD_TREAT_CHECK_AS_ASSERTION 0)
if(BD_TREAT_CHECK_AS_ASSERTION)
add_definitions(-DBD_TREAT_CHECK_AS_ASSERTION)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
set(BD_DEBUG_BUILD 1)
add_definitions(-DBD_DEBUG_BUILD)
endif()

set(BD_ENABLE_PROFILING 1)
if(BD_ENABLE_PROFILING)
add_definitions(-DBD_ENABLE_PROFILING)
endif()

set(BD_POOL_WORKER_WAIT_TIMEOUT 500)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Make sure we're using the correct GloveConfig.h
include_directories(BEFORE ${CMAKE_BINARY_DIR})

configure_file (
  "${PROJECT_SOURCE_DIR}/glove/GloveConfig.hpp.in"
  "${PROJECT_BINARY_DIR}/glove/GloveConfig.hpp"
)

add_definitions(-DBOOST_LOG_DYN_LINK -DGLM_FORCE_RADIANS -DBOOST_ALL_NO_LIB -DGLEW_MX -DBOOST_ALL_DYN_LINK -DHAVE_ROUND)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -DPy_TRACE_REFS -DPy_DEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -DNDEBUG -DRELEASE")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -DRELEASE")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DNDEBUG -DRELEASE")

set(INCLUDE_INSTALL_DIR include)
set(LIB_INSTALL_DIR lib64)
set(MODULE_INSTALL_DIR share/glove/modules)
set(CONFIG_PACKAGE_DIR share/glove/cmake)