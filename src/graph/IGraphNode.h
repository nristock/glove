#ifndef GRAPH_IGRAPHNODE_H_
#define GRAPH_IGRAPHNODE_H_

#include <list>
#include <memory>

#include "core/GloveFwd.h"
#include "memory/GloveMemory.h"

#include "graph/Transform.h"

namespace glove {

class IGraphNode {
	GLOVE_MEM_ALLOC_FUNCS("IGraphNode")
public:
	typedef std::list<IGraphNodePtr> GraphNodeList;
	typedef GraphNodeList::iterator GraphNodeListIterator;

	IGraphNode();
	virtual ~IGraphNode();

	virtual void AttachChild(IGraphNodePtr child) = 0;
	virtual void RemoveChild(IGraphNodePtr child) = 0;
	virtual void OnParented(IGraphNodePtr parent) = 0;
	
	Transform& GetTransform() { return transform; }
	void RefreshTransformTree();
	
protected:
	IGraphNodePtr parent;
	GraphNodeList children;

	Transform transform;
};

} /* namespace glove */

#endif /* GRAPH_IGRAPHNODE_H_ */
