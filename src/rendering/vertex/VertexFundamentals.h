#pragma once

#ifdef VF_MANAGED_DATA
#include "rendering/vertex/ManagedIndexData.h"
#include "rendering/vertex/ManagedVertexData.h"
#else
#include "rendering/vertex/IndexData.h"
#include "rendering/vertex/VertexData.h"
#endif

#include "rendering/vertex/VertexAttribute.h"
#include "rendering/vertex/VertexAttributeSemantic.h"
#include "rendering/vertex/VertexAttributeType.h"

#include "rendering/vertex/VertexLayout.h"
#include "rendering/vertex/VertexLayouts.h"