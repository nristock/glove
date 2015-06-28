#include "GLGpuBuffer.hpp"

namespace BlueDwarf {
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
} /* namespace BlueDwarf */