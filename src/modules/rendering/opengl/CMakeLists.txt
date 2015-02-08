set(opengl_renderer_src
    GLRenderer.cc
    GLWindow.cc
    GLGpuBuffer.cc
    GLMesh.cc
    GLRenderOperation.cc

    internal/GlfwWrapper.cc
    internal/OpenGLWrapper.cc

    target/GLRenderTarget.cc
    target/GLDefaultRenderTarget.cc

    shader/GLMaterialAttribute.cc
    shader/GLMaterial.cc
    shader/GLShader.cc
    shader/GLShaderProgram.cc
    shader/GLVertexAttributeMapping.cc

    factories/GLRendererFactory.cc
    factories/GLRendererSubsystemFactory.cc
    factories/GLGpuBufferFactory.cc
    factories/GLMeshFactory.cc
    factories/GLShaderFactory.cc
    factories/GLShaderProgramFactory.cc
    factories/GLMaterialFactory.cc
    factories/GLRenderOperationFactory.cc

    subsystem/OpenGLRendererModule.cc
    subsystem/GLRendererExtension.cc
    subsystem/GLRendererSubsystemDefinition.cc
    subsystem/GLRendererSubsystem.cc
)

add_library(mod_glrenderer SHARED ${opengl_renderer_src})

install(TARGETS mod_glrenderer EXPORT GloveModuleTargets
        LIBRARY DESTINATION ${MODULE_INSTALL_DIR}
)