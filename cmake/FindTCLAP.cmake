# Locate tclap
# This module defines
# TCLAP_FOUND, if false, do not try to link to tclap
# TCLAP_INCLUDE_DIRS, where to find the headers
#

find_path(TCLAP_INCLUDE_DIRS tclap/CmdLine.h
    PATH_SUFFIXES include
    PATHS
    ${TCLAP_ROOT}
    ${DEPS_PREFIX}/tclap
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /opt
    /usr/freeware
)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TCLAP DEFAULT_MSG TCLAP_INCLUDE_DIRS)
mark_as_advanced(TCLAP_INCLUDE_DIRS)
