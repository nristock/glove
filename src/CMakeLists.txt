cmake_minimum_required(VERSION 2.8)
project(glove)

add_definitions(-DBOOST_LOG_DYN_LINK -DGLM_FORCE_RADIANS -DBOOST_ALL_NO_LIB -DGLEW_MX -DBOOST_ALL_DYN_LINK -DHAVE_ROUND)

if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
	#add_definitions(-DPy_TRACE_REFS -DPy_DEBUG)
endif()

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

	link_directories("${deps_path}/libs/boost")
	link_directories("${deps_path}/libs/glew")
	link_directories("${deps_path}/libs/glfw")
	link_directories("${deps_path}/libs/python")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2 -std=c++11 -pthread")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -Wall -MMD -MP")

	find_package(PythonLibs 3.0 REQUIRED)
	include_directories(${PYTHON_INCLUDE_DIR})
endif()

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(vendor)

file(GLOB_RECURSE glove_sources 
	"buffers/*.cpp"
	"buffers/*.h"
	
	"core/*.cpp"
	"core/*.h"
	
	"event/*.cpp"
	"event/*.h"
	
	"graph/*.cpp"
	"graph/*.h"
	
	"input/*.cpp"
	"input/*.h"
	
	"log/*.cpp"
	"log/*.h"
	
	"pitamem/*.cpp"
	"pitamem/*.h"
	
	"rendering/*.cpp"
	"rendering/*.h"
	
	"resources/*.cpp"
	"resources/*.h"
	
	"scripting/*.cpp"
	"scripting/*.h"
	
	"shader/*.cpp"
	"shader/*.h"
	
	"utils/*.cpp"
	"utils/*.h"
)
add_library(glove ${glove_sources})
target_link_libraries(glove vendor_jsoncpp)

set(cellulose_source main.cpp)
add_executable(cellulose ${cellulose_source})

file(GLOB_RECURSE tests_sources
	"tests/*.cpp"
	"tests/*.h"
)
#add_executable(glove_tests ${tests_sources})
#set_target_properties(glove_tests PROPERTIES COMPILE_DEFINITIONS "GLOVE_TESTS_BUILD")

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
		optimized boost_program_options

		debug boost_thread-d
		debug boost_system-d
		debug boost_date_time-d
		debug boost_filesystem-d
		debug boost_log-d
		debug boost_log_setup-d
        debug boost_program_options-d

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
		boost_program_options
		${PYTHON_LIBRARY}
		glove
	)	
endif()

target_link_libraries(cellulose ${glove_libs})
#target_link_libraries(glove_tests ${glove_libs})

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
