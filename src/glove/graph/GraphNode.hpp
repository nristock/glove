#pragma once

#include <list>

#include "glove/GloveFwd.hpp"
#include "glove/graph/Graph.hpp"
#include "glove/graph/Transform.hpp"

namespace glove {

class GLOVE_API_EXPORT GraphNode : public std::enable_shared_from_this<GraphNode> {
  public:
    typedef std::list<GraphNodeHandle> GraphNodeList;
    typedef GraphNodeList::iterator GraphNodeListIterator;

    GraphNode();
    virtual ~GraphNode();

    virtual void AttachChild(const GraphNodeHandle& child);
    virtual void RemoveChild(const GraphNodeHandle& child);

    Transform& GetTransform();

  protected:
    GraphNodeHandle parent;
    GraphNodeList children;

    Transform transform;

    void RefreshTransformTree();
    virtual void OnParented(const GraphNodeHandle& parent);
};

} /* namespace glove */