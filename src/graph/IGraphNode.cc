#include "graph/IGraphNode.h"

namespace glove {

IGraphNode::IGraphNode() {
    transform.SetModifyCallback([this]() {
        this->RefreshTransformTree();
    });
}

IGraphNode::~IGraphNode() {

}

void IGraphNode::RefreshTransformTree() {
    transform.RecalculateMatrix(false);

    if (parent) transform.RecalculateAccumulatedTransform(parent->GetTransform());
    else transform.RecalculateAccumulatedTransform(Transform::Identity());

    for (auto child : children) {
        child->RefreshTransformTree();
    }
}

} /* namespace glove */
