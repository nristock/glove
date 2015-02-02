# Locate libzip
# This module defines
# LIBZIP_LIBRARY
# LIBZIP_FOUND, if false, do not try to link to libzip 
# LIBZIP_INCLUDE_DIR, where to find the headers
#

find_path(LIBZIP_INCLUDE_DIR zip.h
    $ENV{LIBZIP_DIR}/include
    $ENV{LIBZIP_DIR}
    $ENV{LIBZIP_ROOT}/include
    $ENV{LIBZIP_ROOT}
    ${DEPS_PREFIX}/libzip/include
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /opt/include
    /usr/freeware/include
)

find_library(LIBZIP_LIBRARY 
    NAMES libzip zip
    PATHS
    $ENV{LIBZIP_DIR}/lib
    $ENV{LIBZIP_DIR}
    $ENV{LIBZIP_ROOT}/lib
    $ENV{LIBZIP_ROOT}
    ${DEPS_PREFIX}/lib
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib
    /usr/lib
    /usr/local/lib64
    /usr/lib64
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
    /usr/freeware/lib64
)

set(LIBZIP_FOUND "NO")
if(LIBZIP_LIBRARY AND LIBZIP_INCLUDE_DIR)
    set(LIBZIP_FOUND "YES")
    message(STATUS "Found LibZip ${LIBZIP_LIBRARY}")
endif()
