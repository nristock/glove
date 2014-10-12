#pragma once

#include <list>

#include "core/GloveObject.h"
#include "rendering/vertex/VertexAttribute.h"

namespace glove {

/** A class representing a vertex layout definition */
class VertexLayout : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("VertexLayout")
public:
	/** Type of internal attribute list */
	typedef std::list<VertexAttribute> VertexAttributeList;

	VertexLayout();
	virtual ~VertexLayout();

	/**
	 * Adds a VertexAttribute element to the internal list of vertex attributes.
	 * @param [in] element The element to add to the internal list
	 */
	virtual void AddElement(const VertexAttribute& element);
	/**
	 * Adds a vertex attribute element to the internal list of vertex attributes.
	 * @param [in] binding The buffer binding this attribute belongs to (this is the index the buffer has in the VertexData binding)
	 * @param [in] offset The offset in of the attribute in bytes
	 * @param [in] attributeType The type of the attribute
	 * @param [in] attributeSemantic The attribute's semantic
	 */
	virtual void AddElement(size_t binding, size_t offset, VertexAttributeType attributeType, VertexAttributeSemantic attributeSemantic);

	/** Returns the current number of attributes */
	size_t GetAttributeCount() const { return attributeList.size(); }
	/** Returns the internal attribute list */
	const VertexAttributeList& GetAttributes() const { return attributeList; }
	/** Returns a pointer to a registered vertex attribute */
	const VertexAttribute* GetAttribute(unsigned short index) const;

private:
	VertexAttributeList attributeList;
};


} // namespace glove