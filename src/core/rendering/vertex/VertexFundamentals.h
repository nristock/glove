#pragma once

#ifdef VF_MANAGED_DATA
#include <core/rendering/vertex/ManagedIndexData.h>
#include <core/rendering/vertex/ManagedVertexData.h>
#else
#include <core/rendering/vertex/IndexData.h>
#include <core/rendering/vertex/VertexData.h>
#endif

#include <core/rendering/vertex/VertexAttribute.h>

#include <core/rendering/vertex/VertexLayout.h>
#include <core/rendering/vertex/VertexLayouts.h>