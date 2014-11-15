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

file(GLOB_RECURSE glove_sources
	"buffers/*.cc"
	"buffers/*.h"

	"core/*.cc"
	"core/*.h"

	"event/*.cc"
	"event/*.h"

	"graph/*.cc"
	"graph/*.h"

	"input/*.cc"
	"input/*.h"

	"log/*.cc"
	"log/*.h"

	"pitamem/*.cc"
	"pitamem/*.h"

	"rendering/*.cc"
	"rendering/*.h"

	"resources/*.cc"
	"resources/*.h"

	"scripting/*.cc"
	"scripting/*.h"

	"shader/*.cc"
	"shader/*.h"

	"utils/*.cc"
	"utils/*.h"
)
add_library(glove ${glove_sources})
target_link_libraries(glove vendor_jsoncpp dl)

set(cellulose_source main.cc)
add_executable(cellulose ${cellulose_source})

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

		general glove
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
		glove
	)
endif()

target_link_libraries(cellulose ${glove_libs})

add_subdirectory(tests)

if(WIN32)
	add_custom_command(TARGET cellulose POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${deps_path}/shared"
        $<TARGET_FILE_DIR:cellulose>)
endif()

	add_custom_command(TARGET cellulose POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/../data"
        $<TARGET_FILE_DIR:cellulose>/data)

	add_custom_command(TARGET cellulose POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/../python"
        $<TARGET_FILE_DIR:cellulose>/data/python)

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
