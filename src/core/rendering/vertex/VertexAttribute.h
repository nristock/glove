#pragma once

#include <cstddef>

#include <core/GloveFwd.h>

#include <pitamem/MemoryProfile.h>
#include <core/rendering/vertex/VertexAttributeSemantic.h>
#include <core/rendering/vertex/VertexAttributeType.h>

namespace glove {

/** Represents a vertex attribute */
class VertexAttribute {
Profilable();
public:
    /**
    * @param [in] binding The buffer binding this attribute belongs to (relates to the buffer binding slot in VertexData)
    * @param [in] offset The attribute's offset in bytes
    * @param [in] attributeType The attribute's type
    * @param [in] attributeSemantic The attribute's semantic
    */
	VertexAttribute(std::size_t binding, std::size_t offset, VertexAttributeType attributeType, VertexAttributeSemantic attributeSemantic);

    virtual ~VertexAttribute();

    /** Returns the binding slot */
    GLOVE_INLINE std::size_t GetBindingSlot() const;

    /** Returns the attribute offset */
    GLOVE_INLINE std::size_t GetOffset() const;

    /** Returns the attribute type */
    GLOVE_INLINE VertexAttributeType GetType() const;

    /** Returns the attribute semantic */
    GLOVE_INLINE VertexAttributeSemantic GetSemantic() const;

    /** Returns the number of individual components - e.g. FLOAT3 has 3 float components */
    GLOVE_INLINE std::size_t GetNumberOfComponents() const;

    /** Returns the total size of this attribute in bytes */
    GLOVE_INLINE std::size_t GetSize() const;

protected:
    size_t binding;
    size_t offset;
    VertexAttributeType attributeType;
    VertexAttributeSemantic attributeSemantic;
};


} // namespace glove