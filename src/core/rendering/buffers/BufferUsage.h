#pragma once

namespace glove {

/// @brief BufferUsage is a hint to the implementing render system at how the buffer will be used and accessed allowing
///        it to optimize the data stores. It does not constrain the usage of a buffer in any way.
/// @ingroup RenderSubsystemInterface
enum class BufferUsage {
    /// @brief The data store contents will be modified once and used many times.
    STATIC = 0,

    /// @brief The data store contents will be modified repeatedly and used many times.
    DYNAMIC = 1,
};

} // namespace glove
