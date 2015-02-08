cmake_minimum_required(VERSION 3.0)
project(glove)

set(PROJECT_ROOT "${CMAKE_SOURCE_DIR}/.." CACHE PATH "Root path of the project, i.e. the directory containing the src dir")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_ROOT}/cmake")

include(GenerateExportHeader)
include(BuildSetup)
include(DependencySetup)

######################
######################
if(WIN32)
    message(FATAL_ERROR "Platform temporarily unsupported")

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

add_subdirectory(vendor)
add_subdirectory(glove)
add_subdirectory(modules)
add_subdirectory(utils)

option(BUILD_TESTS "Whether to build tests or not" ON)
if(BUILD_TESTS)
add_subdirectory(tests)
endif()

include(MsvcFiletree)

include(Install)