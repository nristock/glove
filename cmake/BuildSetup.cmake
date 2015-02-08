set(GLOVE_VERSION_MAJOR 1)
set(GLOVE_VERSION_MINOR 0)
set(GLOVE_VERSION_PATCH 0)


##############################################
##############################################
include(GitInfo)

# General Configuration
if(WIN32)
	set(ON_WINDOWS 1)
	add_definitions(-DON_WINDOWS)
else()
	set(ON_UNIX 1)
	add_definitions(-DON_UNIX)
endif()

GetGitInfo(GIT_BRANCH GIT_SHORT_HASH)
message("On branch ${GIT_BRANCH} @ ${GIT_SHORT_HASH}")

set(GLOVE_VERSION ${GLOVE_VERSION_MAJOR}.${GLOVE_VERSION_MINOR}.${GLOVE_VERSION_PATCH})