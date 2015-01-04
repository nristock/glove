#include "GraphNode.h"

namespace glove {

GraphNode::GraphNode() {
}

GraphNode::~GraphNode() {
    children.clear();
}

void GraphNode::RefreshTransformTree() {
    if (parent)
        transform.RecalculateAccumulatedTransform(parent->GetTransform());
    else
        transform.RecalculateAccumulatedTransform(Transform::Identity());

    for (auto child : children) {
        child->RefreshTransformTree();
    }
}

Transform& GraphNode::GetTransform() {
    return transform;
}

void GraphNode::AttachChild(const GraphNodeHandle& child) {
    children.push_back(child);
    child->OnParented(shared_from_this());
}

void GraphNode::RemoveChild(const GraphNodeHandle& child) {
    children.remove(child);
    child->OnParented(GraphNodeHandle());
}

void GraphNode::OnParented(const GraphNodeHandle& parent) {
    this->parent = parent;
    RefreshTransformTree();
}
} /* namespace glove */
