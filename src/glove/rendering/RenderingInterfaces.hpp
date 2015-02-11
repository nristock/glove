#pragma once

#include "glove/rendering/factories/IGpuBufferFactory.hpp"
#include "glove/rendering/factories/IMaterialFactory.hpp"
#include "glove/rendering/factories/IMeshFactory.hpp"
#include "glove/rendering/factories/IRendererFactory.hpp"
#include "glove/rendering/factories/IShaderFactory.hpp"
#include "glove/rendering/factories/IShaderProgramFactory.hpp"

#include "glove/rendering/vertex/IIndexData.hpp"
#include "glove/rendering/vertex/IVertexAttributeMapping.hpp"
#include "glove/rendering/vertex/IVertexData.hpp"

#include "glove/rendering/shader/IMaterial.hpp"
#include "glove/rendering/shader/IMaterialAttribute.hpp"
#include "glove/rendering/shader/IShader.hpp"
#include "glove/rendering/shader/IShaderProgram.hpp"

#include "glove/rendering/target/IRenderTarget.hpp"

#include "glove/rendering/mesh/IMesh.hpp"

#include "glove/rendering/IRenderer.hpp"
#include "glove/rendering/IRenderSubsystem.hpp"
#include "glove/rendering/IWindow.hpp"
#include "glove/rendering/IRenderOperation.hpp"

#include "glove/rendering/FrameData.hpp"
#include "glove/rendering/RenderOperation.hpp"
#include "glove/rendering/WindowConstructionHints.hpp"