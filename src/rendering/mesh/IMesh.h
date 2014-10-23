#pragma once

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

/** A class abstracting mesh funcionality */
class IMesh {
public:
    virtual ~IMesh() {
    };

    /** Refresh the mesh (e.g. update vertex attribute bindings to the material)  */
    virtual void Refresh() = 0;

    /** Returns the associated material */
    virtual const MaterialPtr& GetMaterial() const = 0;

    /** Returns the associated vertex data */
    virtual const VertexDataPtr& GetVertexData() const = 0;

    /** Returns the associated index data (if any) */
    virtual const IndexDataPtr& GetIndexData() const = 0;

    /** Returns the associated shader program */
    virtual const ShaderProgramPointer& GetShader() const = 0;

    /** Creates index data. (This includes a GPU buffer for indices) */
    virtual void CreateIndexData() = 0;
};


} // namespace glove