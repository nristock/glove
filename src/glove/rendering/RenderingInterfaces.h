#pragma once

#include "glove/rendering/factories/IGpuBufferFactory.h"
#include "glove/rendering/factories/IMaterialFactory.h"
#include "glove/rendering/factories/IMeshFactory.h"
#include "glove/rendering/factories/IRendererFactory.h"
#include "glove/rendering/factories/IShaderFactory.h"
#include "glove/rendering/factories/IShaderProgramFactory.h"

#include "glove/rendering/vertex/IIndexData.h"
#include "glove/rendering/vertex/IVertexAttributeMapping.h"
#include "glove/rendering/vertex/IVertexData.h"

#include "glove/rendering/shader/IMaterial.h"
#include "glove/rendering/shader/IMaterialAttribute.h"
#include "glove/rendering/shader/IShader.h"
#include "glove/rendering/shader/IShaderProgram.h"

#include "glove/rendering/target/IRenderTarget.h"

#include "glove/rendering/mesh/IMesh.h"

#include "glove/rendering/IRenderer.h"
#include "glove/rendering/IRenderSubsystem.h"
#include "glove/rendering/IWindow.h"
#include "glove/rendering/IRenderOperation.h"

#include "glove/rendering/FrameData.h"
#include "glove/rendering/RenderOperation.h"
#include "glove/rendering/WindowConstructionHints.h"