#pragma once

#include <glm/glm.hpp>

#include "glove/rendering/vertex/VertexLayout.h"
#include "glove/rendering/vertex/VertexAttributeUtils.h"
#include "glove/rendering/vertex/VertexAttributeSemantic.h"

namespace glove {

/// @defgroup VertexLayouts
/// Predefined vertex layouts. <br/>
/// All layouts provide GetLayout(size_t bufferIndex = 0) functions returning a VertexLayout instance.

namespace VertexLayouts {

/// @brief Position-only vertex layout.
/// @ingroup VertexLayouts
///
/// This layout consists of a single float[3] (glm::vec3) for position data
struct Position {
    glm::vec3 position;

    static VertexLayout GetLayout(size_t bufferIndex) {
        VertexLayout layout;
        layout.AddAttribute({bufferIndex, 0, VertexAttributeType::FLOAT3, VertexAttributeSemantic::POSITION});

        return layout;
    }

    static VertexLayout GetLayout() { return GetLayout(0); }

    GLOVE_INLINE bool operator==(const Position& other) const { return position == other.position; }
};

/// @brief Position+Normal vertex layout.
/// @ingroup VertexLayouts
///
/// This layout consists of a two float[3] (glm::vec3) for position and normal data
struct PositionNormal {
    glm::vec3 position;
    glm::vec3 normal;

    static VertexLayout GetLayout(size_t bufferIndex) {
        VertexLayout layout;
        layout.AddAttribute({bufferIndex, 0, VertexAttributeType::FLOAT3, VertexAttributeSemantic::POSITION});
        layout.AddAttribute({bufferIndex, VertexAttributeUtils<VertexAttributeType::FLOAT3>::GetTypeSize(),
                           VertexAttributeType::FLOAT3, VertexAttributeSemantic::NORMAL});

        return layout;
    }

    static VertexLayout GetLayout() { return GetLayout(0); }

    GLOVE_INLINE bool operator==(const PositionNormal& other) const {
        return position == other.position && normal == other.normal;
    }
};

/// @brief Position+Color vertex layout.
/// @ingroup VertexLayouts
///
/// This layout consists of a single float[3] (glm::vec3) for position and a float[4] (glm::vec4) for color data
struct PositionColor {
    glm::vec3 position;
    glm::vec4 color;

    static VertexLayout GetLayout(size_t bufferIndex) {
        VertexLayout layout;
        layout.AddAttribute({bufferIndex, 0, VertexAttributeType::FLOAT3, VertexAttributeSemantic::POSITION});
        layout.AddAttribute({bufferIndex, VertexAttributeUtils<VertexAttributeType::FLOAT3>::GetTypeSize(),
                           VertexAttributeType::FLOAT4, VertexAttributeSemantic::COLOR});

        return layout;
    }

    static VertexLayout GetLayout() { return GetLayout(0); }

    GLOVE_INLINE bool operator==(const PositionColor& other) const {
        return position == other.position && color == other.color;
    }
};
}
} /* namespace glove */