#pragma once

#include <memory>
#include <map>

#include <glm/glm.hpp>

/// @defgroup RenderSubsystemInterface
/// Rendering Subsystem Interface

namespace glove {

/// @addtogroup RenderSubsystemInterface
/// @{

class IGpuBufferFactory;
class IGpuBuffer;

class IMeshFactory;

class IRendererFactory;
class IRenderer;
class IRenderSubsystem;
class IRenderable;

class IRenderOperation;
class IRenderOperationFactory;

class IShaderFactory;
class IShaderProgramFactory;

class IWindow;

class WindowConstructionHints;
class VertexLayout;
class VertexAttribute;

class IIndexData;
class IVertexData;
class IMaterialFactory;
class IMaterial;
class IVertexAttributeMapping;
class IShader;
class IShaderProgram;
class IMesh;
class IMaterialAttribute;
class MaterialTextureAttribute;
class IRenderTarget;

class Texture;
class TextureFactory;

typedef std::shared_ptr<IGpuBufferFactory> IGpuBufferFactoryPtr;
typedef std::shared_ptr<IGpuBuffer> IGpuBufferPtr;

typedef std::shared_ptr<IMeshFactory> IMeshFactoryPtr;

typedef std::shared_ptr<IRendererFactory> IRendererFactoryPtr;
typedef std::shared_ptr<IRenderer> IRendererPtr;

typedef std::shared_ptr<IRenderable> IRenderablePtr;
typedef std::shared_ptr<IRenderTarget> RenderTargetHandle;

typedef std::shared_ptr<IShaderFactory> IShaderFactoryPtr;

typedef std::shared_ptr<IWindow> IWindowPtr;

typedef std::shared_ptr<IIndexData> IIndexDataPtr;
typedef std::shared_ptr<IVertexData> IVertexDataPtr;
typedef std::shared_ptr<IMaterial> IMaterialPtr;
typedef std::shared_ptr<IVertexAttributeMapping> IVertexAttributeMappingPtr;
typedef std::shared_ptr<IShader> IShaderPtr;
typedef std::shared_ptr<IShaderProgram> IShaderProgramPtr;
typedef std::shared_ptr<IMesh> IMeshPtr;
typedef std::shared_ptr<IMaterialAttribute> IMaterialAttributePtr;
typedef std::shared_ptr<MaterialTextureAttribute> MaterialTextureAttributeHandle;
typedef std::shared_ptr<IRenderSubsystem> IRenderSubsystemPtr;
typedef std::shared_ptr<IShaderProgramFactory> IShaderProgramFactoryPtr;
typedef std::shared_ptr<IMaterialFactory> IMaterialFactoryPtr;

typedef std::shared_ptr<IRenderOperationFactory> RenderOperationFactoryHandle;

typedef std::shared_ptr<Texture> TextureHandle;
typedef std::shared_ptr<TextureFactory> TextureFactoryHandle;

/// @brief The type of the buffer binding map (slot <-> buffer)
typedef std::map<std::size_t, IGpuBufferPtr> VertexBufferBindingMap;

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;

typedef Vector2 Point;

typedef glm::ivec2 IntVector2;
typedef glm::ivec3 IntVector3;

typedef IntVector2 IntPoint;
typedef IntVector2 IntLocation;
typedef IntVector2 ScreenPoint;

/// @}

} /* namespace glove */