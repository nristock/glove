cmake_minimum_required(VERSION 3.0)
project(glove)

set(PROJECT_ROOT "${CMAKE_SOURCE_DIR}/.." CACHE PATH "Root path of the project, i.e. the directory containing the src dir")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_ROOT}/cmake")

include(GenerateExportHeader)
include(BuildSetup)

if(WIN32)
option (USE_PREBUILT_DEPS "Set up variables to prefer prebuilt dependencies over system libraries" ON)
else()
option (USE_PREBUILT_DEPS "Set up variables to prefer prebuilt dependencies over system libraries" OFF)
endif()

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

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Dependency Config Options
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

if(WIN32)
    set(DEPS_PREFIX "${PROJECT_ROOT}/deps/win64" CACHE PATH "Root of the directory containing dependencies")
else()
    set(DEPS_PREFIX "${PROJECT_ROOT}/deps/linux64" CACHE PATH "Root of the directory containing dependencies")
endif()

if(USE_PREBUILT_DEPS)
    set(ZLIB_ROOT "${DEPS_PREFIX}/zlib" CACHE STRING "Zlib install directory")
    set(PNG_ROOT "${DEPS_PREFIX}/png" CACHE STRING "libpng install directory")
    set(LIBZIP_ROOT "${DEPS_PREFIX}/libzip" CACHE STRING "libzip install directory")
    set(BOOST_ROOT "${DEPS_PREFIX}/boost" CACHE STRING "Boost install directory")
    set(PYTHON_ROOT "${DEPS_PREFIX}/python" CACHE STRING "Python install directory")
    set(TCLAP_ROOT "${DEPS_PREFIX}/tclap" CACHE STRING "Tclap install directory")
    set(YAMLCPP_ROOT "${DEPS_PREFIX}/yaml-cpp" CACHE STRING "Yaml-cpp install directory")
endif()

find_package(Threads REQUIRED)

find_package(Boost 1.55 REQUIRED COMPONENTS thread system date_time filesystem log log_setup)
include_directories(${Boost_INCLUDE_DIRS})

find_package(ZLIB 1.2.8 REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

find_package(PNG 1.6 REQUIRED)
include_directories(${PNG_INCLUDE_DIRS})

find_package(LibZip 0.11.2 REQUIRED)
include_directories(${LIBZIP_INCLUDE_DIRS})

find_package(PythonLibs 3.4 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(TCLAP 1.2.1 REQUIRED)
include_directories(${TCLAP_INCLUDE_DIRS})

find_package(YamlCpp 0.5.1 REQUIRED)
include_directories(${YAMLCPP_INCLUDE_DIRS})

######################
######################
if(WIN32)
	set(deps_path "${CMAKE_SOURCE_DIR}/../deps/win64")

	if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2 /GR")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Od /GR" CACHE INTERNAL "" FORCE)
    endif()

    if(MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2 -std=c++11")
       	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -Wall -MMD -MP")
    endif()
	
	include_directories("${deps_path}/glew/include")
	include_directories("${deps_path}/glfw/include")
	include_directories("${deps_path}/glm/include")
	include_directories("${deps_path}/python/include")
	include_directories("${deps_path}/tclap/include")

	link_directories("${deps_path}/glew/libs")
	link_directories("${deps_path}/glfw/libs")
	link_directories("${deps_path}/python/libs")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2 -std=c++14 -pthread -fPIC")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -Wall -MMD -MP")
endif()

include_directories(${CMAKE_SOURCE_DIR})

if(WIN32)
	set(glove_libs
		general glfw3
		general OpenGL32
		general GLEWmx
	)
else()
	set(glove_libs
		${CMAKE_THREAD_LIBS_INIT}
		glfw
		GL
		GLEWmx
		GLU
		${Boost_LIBRARIES}
		${ZLIB_LIBRARIES}
		${PNG_LIBRARIES}
		${LIBZIP_LIBRARIES}
		${PYTHON_LIBRARIES}
		${YAMLCPP_LIBRARIES}
	)
endif()

set(INCLUDE_INSTALL_DIR include)
set(LIB_INSTALL_DIR lib64)
set(MODULE_INSTALL_DIR share/glove/modules)
set(CONFIG_PACKAGE_DIR share/glove/cmake)

add_subdirectory(vendor)
add_subdirectory(glove)
add_subdirectory(modules)
add_subdirectory(utils)

option(BUILD_TESTS "Whether to build tests or not" ON)
if(BUILD_TESTS)
add_subdirectory(tests)
endif()

include(MsvcFiletree)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/glove/GloveVersion.cmake"
  VERSION ${GLOVE_VERSION}
  COMPATIBILITY SameMajorVersion
)

export(EXPORT GloveTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/glove/GloveTargets.cmake"
  NAMESPACE Glove::
)

configure_package_config_file(
    "${PROJECT_ROOT}/cmake/GloveConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/glove/GloveConfig.cmake"
    INSTALL_DESTINATION ${CONFIG_PACKAGE_DIR}
    PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR MODULE_INSTALL_DIR
)

install(EXPORT GloveTargets
  FILE
    GloveTargets.cmake
  NAMESPACE
    Glove::
  DESTINATION
    ${CONFIG_PACKAGE_DIR}
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/glove/GloveConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/glove/GloveVersion.cmake"
  DESTINATION
    ${CONFIG_PACKAGE_DIR}
)