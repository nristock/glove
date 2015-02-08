# Locate libzip
# This module defines
# LIBZIP_LIBRARY
# LIBZIP_FOUND, if false, do not try to link to libzip 
# LIBZIP_INCLUDE_DIRS, where to find the headers
#

find_path(LIBZIP_INCLUDE_DIRS zip.h
    PATH_SUFFIXES include
    PATHS
    ${LIBZIP_ROOT}
    ${DEPS_PREFIX}/libzip
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /opt
    /usr/freeware
)

find_library(LIBZIP_LIBRARIES
    NAMES libzip zip
    PATH_SUFFIXES lib64 lib
    PATHS
    ${LIBZIP_ROOT}
    ${DEPS_PREFIX}/libzip
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt
    /usr/freeware
)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibZip DEFAULT_MSG LIBZIP_INCLUDE_DIRS LIBZIP_LIBRARIES)
mark_as_advanced(LIBZIP_INCLUDE_DIRS LIBZIP_LIBRARIES)
