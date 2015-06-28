set(opengl_renderer_src
    GLWindow.cc

    internal/GlfwWrapper.cc
    internal/OpenGLWrapper.cc

    factories/GLWindowFactory.cc

    subsystem/OpenGLRendererModule.cc
    subsystem/GLRenderingModule.cc

    new/GLRenderResourceFactory.cc
    new/GLVertexBinding.cc
    new/VertexElementUtils.cc
    new/GLGpuBuffer.cc
    new/GLRenderHardwareInterface.cc
    new/GLState.hpp
    new/GLTexture.hpp
    new/GLShader.cc
    new/GLTexture.cc
)

include_directories(.)
include_directories(${CMAKE_SOURCE_DIR})

add_library(mod_glrenderer SHARED ${opengl_renderer_src})

install(TARGETS mod_glrenderer EXPORT GloveModuleTargets
        LIBRARY DESTINATION ${MODULE_INSTALL_DIR}
)