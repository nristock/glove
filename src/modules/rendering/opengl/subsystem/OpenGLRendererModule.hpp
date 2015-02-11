#pragma once

#include <memory>

/// @defgroup OpenGLRenderer
/// Render system implementation for OpenGL using GLFW for window system interaction.

/// @defgroup Factories
/// @ingroup OpenGLRenderer
/// Factory implementations

/// @defgroup Shader
/// @ingroup OpenGLRenderer

/// @defgroup Internal
/// @ingroup OpenGLRenderer

namespace glove {
namespace gl {

/// @addtogroup OpenGLRenderer
/// @{
class GLGpuBufferFactory;
class GLMaterial;
class GLMaterialFactory;
class GLMesh;
class GLMeshFactory;
class GLRenderer;
class GLRendererFactory;
class GLRendererSubsystem;
class GLRendererSubsystemDefinition;
class GLRenderOperation;
class GLRenderOperationFactory;
class GLShader;
class GLShaderFactory;
class GLShaderProgram;
class GLShaderProgramFactory;
class GLWindow;

class OpenGLWrapper;
class GlfwWrapper;

typedef std::shared_ptr<GLWindow> GLWindowPtr;
typedef std::shared_ptr<GLRenderer> GLRendererPtr;
typedef std::shared_ptr<GLRendererFactory> GLRendererFactoryPtr;
typedef std::shared_ptr<GLRendererSubsystem> GLRendererSubsystemPtr;
typedef std::shared_ptr<GLShaderProgram> GLShaderProgramPtr;
typedef std::shared_ptr<GLMaterial> GLMaterialPtr;
typedef std::weak_ptr<GLMaterial> GLMaterialRef;
typedef std::shared_ptr<GLShader> GLShaderPtr;
typedef std::shared_ptr<OpenGLWrapper> OpenGLWrapperPtr;
typedef std::shared_ptr<GLMesh> GLMeshPtr;
typedef std::shared_ptr<GLRendererSubsystemDefinition> GLRendererSubsystemDefinitionPtr;
typedef std::shared_ptr<GLShaderProgramFactory> GLShaderProgramFactoryPtr;
typedef std::shared_ptr<GLGpuBufferFactory> GLGpuBufferFactoryPtr;
typedef std::shared_ptr<GLShaderFactory> GLShaderFactoryPtr;
typedef std::shared_ptr<GLMeshFactory> GLMeshFactoryPtr;
typedef std::shared_ptr<GLMaterialFactory> GLMaterialFactoryPtr;
typedef std::shared_ptr<GlfwWrapper> GlfwWrapperPtr;
typedef std::shared_ptr<GLRenderOperationFactory> GLRenderOperationFactoryHandle;

typedef uint16_t ContextId;

typedef OpenGLWrapper GL;
/// @}
}
} /* namespace glove */