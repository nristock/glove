set(GLOVE_VERSION_MAJOR 1)
set(GLOVE_VERSION_MINOR 0)
set(GLOVE_VERSION_PATCH 0)

option(GLOVE_BUILD_TESTS "Whether to build tests or not" ON)
option(GLOVE_BUILD_MODULES "Whether to build modules or not" ON)

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

set(GLOVE_VERSION ${GLOVE_VERSION_MAJOR}.${GLOVE_VERSION_MINOR}.${GLOVE_VERSION_PATCH})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Make sure we're using the correct GloveConfig.h
include_directories(BEFORE ${CMAKE_BINARY_DIR})

configure_file (
  "${PROJECT_SOURCE_DIR}/GloveConfig.h.in"
  "${PROJECT_BINARY_DIR}/GloveConfig.h"
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