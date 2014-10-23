#pragma once

#include "core/GloveFwd.h"
#include "pitamem/MemoryProfile.h"

namespace glove {

/** A structure representing a single render operation for passive rendering */
struct RenderOperation {
Profilable()
public:
    RenderOperation();

    virtual ~RenderOperation();

    /** Resets the structure */
    void Reset();

    /** Vertex data to use for rendering (must not be null) */
    VertexData* vertexData;
    /** Index data to use for rendering (can be null) */
    IndexData* indexData;
    /** Material to use for rendering (must not be null) */
    Material* material;
};


} // namespace glove