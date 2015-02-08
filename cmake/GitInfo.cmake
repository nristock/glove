# Git info module

function(GetGitBranchName _var)
    execute_process(
    	COMMAND git rev-parse --abbrev-ref HEAD
    	OUTPUT_VARIABLE GIT_BRANCH_NAME
    	OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(${_var} ${GIT_BRANCH_NAME} PARENT_SCOPE)
endfunction()

function(GetGitShortHash _var)
    execute_process(
    	COMMAND git rev-parse --short HEAD
    	OUTPUT_VARIABLE GIT_SHORT_HASH
    	OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(${_var} ${GIT_SHORT_HASH} PARENT_SCOPE)
endfunction()

function(GetGitInfo _branch _shortHash)
    GetGitBranchName(GIT_BRANCH)
    GetGitShortHash(GIT_SHORT_HASH)
    set(${_branch} ${GIT_BRANCH} PARENT_SCOPE)
    set(${_shortHash} ${GIT_SHORT_HASH} PARENT_SCOPE)
endfunction()