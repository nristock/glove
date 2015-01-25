cmake_minimum_required(VERSION 3.0)
project(glove)

if(WIN32)
option (USE_PREBUILT_DEPS "Set up variables to prefer prebuilt dependencies over system libraries" ON)
else()
option (USE_PREBUILT_DEPS "Set up variables to prefer prebuilt dependencies over system libraries" OFF)
endif()

set(GLOVE_VERSION_MAJOR 1)
set(GLOVE_VERSION_MINOR 0)
set(GLOVE_VERSION_PATCH 0)

# General Configuration
if(WIN32)
	set(ON_WINDOWS 1)
	add_definitions(-DON_WINDOWS)
else()
	set(ON_UNIX 1)
	add_definitions(-DON_UNIX)
endif()

add_definitions(-DBOOST_LOG_DYN_LINK -DGLM_FORCE_RADIANS -DBOOST_ALL_NO_LIB -DGLEW_MX -DBOOST_ALL_DYN_LINK -DHAVE_ROUND)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -DPy_TRACE_REFS -DPy_DEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -DNDEBUG -DRELEASE")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -DRELEASE")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DNDEBUG -DRELEASE")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Make sure we're using the correct GloveConfig.h
include_directories(BEFORE ${CMAKE_BINARY_DIR})

configure_file (
  "${PROJECT_SOURCE_DIR}/GloveConfig.h.in"
  "${PROJECT_BINARY_DIR}/GloveConfig.h"
)

# Dependency Config Options
set(PROJECT_ROOT "${CMAKE_SOURCE_DIR}/.." CACHE PATH "Root path of the project, i.e. the directory containing the src dir")

if(WIN32)
set(DEPS_PREFIX "${PROJECT_ROOT}/deps/win64" CACHE PATH "Root of the directory containing dependencies")
else()
set(DEPS_PREFIX "${PROJECT_ROOT}/deps/linux64" CACHE PATH "Root of the directory containing dependencies")
endif()

# Python 3.x
# Use the "standard" $PREFIX/<bin|include|lib> convention on most UNIX systems to find binary, include and lib directories
# Then use the python executable to build the library name
# 		python[version.major].[version.minor][abiflags].[so|a]
set(DEPS_PYTHON_PATH "${DEPS_PREFIX}/python3" CACHE PATH "Root of a python 3.x installation")
set(DEPS_PYHTON_BIN "${DEPS_PYTHON_PATH}/bin" CACHE PATH "Directory containing python binary")
set(DEPS_PYTHON_INC "${DEPS_PYTHON_PATH}/include" CACHE PATH "Python include directory")
set(DEPS_PYTHON_LIBS "${DEPS_PYTHON_PATH}/lib" CACHE PATH "Python library directory")

set(DEPS_PYTHON_EXECUTABLE "${DEPS_PYHTON_BIN}/python" CACHE STRING "Python executable")

execute_process(
	COMMAND ${DEPS_PYTHON_EXECUTABLE} -c "import sys; print(sys.abiflags)"
	OUTPUT_VARIABLE TMP_PYTHON_ABI_TAG
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(DEPS_PYTHON_ABI "${TMP_PYTHON_ABI_TAG}" CACHE STRING "Python build abi information")

execute_process(
	COMMAND ${DEPS_PYTHON_EXECUTABLE} -c "import sys; print('{0}.{1}'.format(sys.version_info.major, sys.version_info.minor))"
	OUTPUT_VARIABLE TMP_PYTHON_VERSION
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(DEPS_PYTHON_VERSION "${TMP_PYTHON_VERSION}" CACHE STRING "Python version (major.minor)")

set(DEPS_PYTHON_LINK_LIBS "python${DEPS_PYTHON_VERSION}${DEPS_PYTHON_ABI}" CACHE STRING "Python library to link against")

if(USE_PREBUILT_DEPS)
set(BOOST_ROOT "${DEPS_PREFIX}/boost" CACHE STRING "Boost root directory")
endif()

find_package(Boost 1.55 REQUIRED COMPONENTS thread system date_time filesystem log log_setup)
include_directories(${Boost_INCLUDE_DIRS})

######################
######################
link_directories(${DEPS_PYTHON_LIBS})

include_directories(vendor/yaml-cpp/include)

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
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2 -std=c++11 -pthread")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -Wall -MMD -MP")
endif()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/core)

add_subdirectory(vendor)

add_subdirectory(core)
add_subdirectory(modules)
add_subdirectory(utils)

if(WIN32)
	set(glove_libs
		general glfw3
		general OpenGL32
		general GLEWmx

		general glove_core
	)
else()
	set(glove_libs
		pthread
		glfw
		GL
		GLEWmx
		GLU
		boost_thread
		boost_system
		boost_date_time
		boost_filesystem
		boost_log
		boost_log_setup
		glove_core
	)
endif()

add_subdirectory(tests)
add_subdirectory(cellulose)

# Fix source tree representation in Visual Studio
if(MSVC)
	macro(GroupSources curdir)
		file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

	    foreach(child ${children})
			if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
	        	GroupSources(${curdir}/${child})
	        else()
	            string(REPLACE "/" "\\" groupname ${curdir})
	            string(REPLACE "." "src" groupname ${groupname})

	            source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
	        endif()
	    endforeach()
	endmacro()

	GroupSources(.)
endif()
