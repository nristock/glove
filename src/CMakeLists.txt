cmake_minimum_required(VERSION 2.8)
project(glove)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g3 -msse2 -std=c++11 -Wall -MMD -MP -pthread -DBOOST_LOG_DYN_LINK -DGLM_FORCE_RADIANS")

file(GLOB_RECURSE glove_sources 
	"*.cpp"
	"*.h"
)
add_library(glove ${glove_sources})

set(cellulose_source main.cpp)
add_executable(cellulose ${cellulose_source})

set(glove_libs
	pthread
	glut
	GL
	GLEW
	GLU
	boost_thread
	boost_system
	boost_date_time
	boost_filesystem
	boost_log
	boost_log_setup
	glove
)
	
target_link_libraries(cellulose ${glove_libs})
