cmake_minimum_required(VERSION 2.8)
project(glove)

set(GLOVE_VERSION_MAJOR 1)
set(GLOVE_VERSION_MINOR 0)
set(GLOVE_VERSION_PATCH 0)

if(WIN32)
	set(ON_WINDOWS 1)
	add_definitions(-DON_WINDOWS)
else()
	set(ON_UNIX 1)
	add_definitions(-DON_UNIX)
endif()

add_definitions(-DBOOST_LOG_DYN_LINK -DGLM_FORCE_RADIANS -DBOOST_ALL_NO_LIB -DGLEW_MX -DBOOST_ALL_DYN_LINK -DHAVE_ROUND)

if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
	#add_definitions(-DPy_TRACE_REFS -DPy_DEBUG)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(BEFORE ${CMAKE_BINARY_DIR})

configure_file (
  "${PROJECT_SOURCE_DIR}/GloveConfig.h.in"
  "${PROJECT_BINARY_DIR}/GloveConfig.h"
)

if(WIN32)
	set(deps_path "${CMAKE_SOURCE_DIR}/../deps/windows")

	if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2 /GR")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Od /GR" CACHE INTERNAL "" FORCE)
    endif()

    if(MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2 -std=c++11")
       	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -Wall -MMD -MP")
    endif()

	include_directories("${deps_path}/include/boost")
	include_directories("${deps_path}/include/glew")
	include_directories("${deps_path}/include/glfw")
	include_directories("${deps_path}/include/glm")
	include_directories("${deps_path}/include/python")
	include_directories("${deps_path}/include/tclap")

	link_directories("${deps_path}/libs/boost")
	link_directories("${deps_path}/libs/glew")
	link_directories("${deps_path}/libs/glfw")
	link_directories("${deps_path}/libs/python")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2 -std=c++11 -pthread")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -Wall -MMD -MP -DDEBUG")

	find_package(PythonLibs 3.0 REQUIRED)
	include_directories(${PYTHON_INCLUDE_DIR})
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
		general boost_python3
		general python34

		optimized boost_thread
		optimized boost_system
		optimized boost_date_time
		optimized boost_filesystem
		optimized boost_log
		optimized boost_log_setup

		debug boost_thread-d
		debug boost_system-d
		debug boost_date_time-d
		debug boost_filesystem-d
		debug boost_log-d
		debug boost_log_setup-d

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
		boost_python3
		${PYTHON_LIBRARY}
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
