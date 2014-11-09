#pragma once

#include <list>

#include "core/GloveFwd.h"

#include <core/graph/Transform.h>

namespace glove {

class IGraphNode {
public:
    typedef std::list<IGraphNodePtr> GraphNodeList;
    typedef GraphNodeList::iterator GraphNodeListIterator;

    IGraphNode();

    virtual ~IGraphNode();

    virtual void AttachChild(IGraphNodePtr child) = 0;

    virtual void RemoveChild(IGraphNodePtr child) = 0;

    virtual void OnParented(IGraphNodePtr parent) = 0;

    Transform& GetTransform() {
        return transform;
    }

    void RefreshTransformTree();

protected:
    IGraphNodePtr parent;
    GraphNodeList children;

    Transform transform;
};

} /* namespace glove */