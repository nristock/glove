#ifndef RENDERING_VERTEX_VERTEXLAYOUTS_H_
#define RENDERING_VERTEX_VERTEXLAYOUTS_H_

#include <glm/glm.hpp>

#include "rendering/vertex/VertexLayout.h"

namespace glove {
/** 
 * Pre-defined vertex layouts 
 * All layouts provide GetLayout(size_t bufferIndex = 0) functions returning a VertexLayout instance
 */
namespace vertexlayouts {

/** 
 * Position-only vertex layout. 
 * This layout consists of a single float[3] (glm::vec3) for position data
 */
struct Position {
	glm::vec3 position;

	static VertexLayout GetLayout(size_t bufferIndex) {
		VertexLayout layout;
		layout.AddElement(bufferIndex, 0, VAT_FLOAT3, VAS_POSITION);

		return layout;
	}

	static VertexLayout GetLayout() {
		return GetLayout(0);
	}
};

/**
* Position+Normal vertex layout.
* This layout consists of a two float[3] (glm::vec3) for position and normal data
*/
struct PositionNormal {
	glm::vec3 position;
	glm::vec3 normal;

	static VertexLayout GetLayout(size_t bufferIndex) {
		VertexLayout layout;
		layout.AddElement(0, 0, VAT_FLOAT3, VAS_POSITION);
		layout.AddElement(bufferIndex, VertexAttribute::GetSize(VAT_FLOAT3), VAT_FLOAT3, VAS_NORMAL);

		return layout;
	}

	static VertexLayout GetLayout() {
		return GetLayout(0);
	}
};

/**
* Position+Color vertex layout.
* This layout consists of a single float[3] (glm::vec3) for position and a float[4] (glm::vec4) for color data
*/
struct PositionColor {
	glm::vec3 position;
	glm::vec4 color;

	static VertexLayout GetLayout(size_t bufferIndex) {
		VertexLayout layout;
		layout.AddElement(0, 0, VAT_FLOAT3, VAS_POSITION);
		layout.AddElement(bufferIndex, VertexAttribute::GetSize(VAT_FLOAT3), VAT_FLOAT4, VAS_COLOR);

		return layout;
	}

	static VertexLayout GetLayout() {
		return GetLayout(0);
	}
};


}
} /* namespace glove */

#endif /* RENDERING_VERTEXLAYOUTS_H_ */
