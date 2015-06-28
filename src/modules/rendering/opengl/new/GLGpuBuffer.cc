#include "GLGpuBuffer.hpp"

namespace glove {
namespace gl {
GLenum GLBufferUtils::BufferMapModeToGlAccessMode(BufferMappingMode mappingMode) {
    switch (mappingMode) {
        case BufferMappingMode::ReadOnly:
            return GL_READ_ONLY;

        case BufferMappingMode::WriteOnly:
            return GL_WRITE_ONLY;

        case BufferMappingMode::ReadWrite:
            return GL_READ_WRITE;
    }
}
}
} /* namespace glove */