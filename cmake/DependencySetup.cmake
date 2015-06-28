if(WIN32)
option (USE_PREBUILT_DEPS "Set up variables to prefer prebuilt dependencies over system libraries" ON)
else()
option (USE_PREBUILT_DEPS "Set up variables to prefer prebuilt dependencies over system libraries" OFF)
endif()

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

find_package(TCLAP 1.2.1 REQUIRED)
include_directories(${TCLAP_INCLUDE_DIRS})

find_package(YamlCpp 0.5.1 REQUIRED)
include_directories(${YAMLCPP_INCLUDE_DIRS})
