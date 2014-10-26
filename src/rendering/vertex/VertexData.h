#pragma once

#include <map>

#include "core/GloveFwd.h"

#include "rendering/vertex/VertexLayout.h"
#include <pitamem/MemoryProfile.h>

namespace glove {

/**
* A class representing generic vertex data.
* Vertex data consists of one or more hardware/GPU buffers and a corresponding VertexLayout.
* This class does not cover any vertex data read-back operations. You can either use the buffer's read functions or ManagedVertexData.
*/
class VertexData {
Profilable();
public:
    /** The type of the buffer binding map (slot <-> buffer) */
	typedef std::map<unsigned short, IGpuBufferPtr> VertexBufferBindingMap;

	VertexData();

    virtual ~VertexData();

    /** Binds a hardware/GPU buffer to the specified slot
    * @param [in] index The slot index to bind the buffer to
    * @param [in] buffer The buffer to bind
    */
	virtual void SetBufferBinding(unsigned short index, const IGpuBufferPtr& buffer);

    /** Returns the curretn number of bound buffers */
    virtual size_t GetBufferCount() const {
        return bufferBindingMap.size();
    }

    /** Returns the internal buffer binding map */
    virtual const VertexBufferBindingMap& GetBindings() const {
        return bufferBindingMap;
    }

    /** Returns the buffer bound to slot @p index */
	virtual const IGpuBufferPtr& GetBuffer(unsigned short index) const;

    /** Returns a pointer to the VertexLayout instance associated with this VertexData object. This does not impose shared ownership. Do not store the pointer for more than one frame. */
    virtual VertexLayout* GetVertexLayout() {
        return &vertexLayout;
    }

    /** Returns the number of vertices */
    virtual size_t GetVertexCount() const {
        return vertexCount;
    }

    /** Sets the number of vertices */
    virtual void SetVertexCount(size_t vertexCount) {
        this->vertexCount = vertexCount;
    }

protected:
    VertexBufferBindingMap bufferBindingMap;

    VertexLayout vertexLayout;

private:
    size_t vertexCount;
};


} // namespace glove