#pragma once

namespace glove {

/**
* Enum describing buffer usage
*/
enum BufferUsage {
    /** Write-once data store (GL_STATIC_DRAW) */
    BU_STATIC = 0,

    /** Data store will be modified repeatedly (GL_DYNAMIC_DRAW) */
    BU_DYNAMIC = 1,
};

} // namespace glove